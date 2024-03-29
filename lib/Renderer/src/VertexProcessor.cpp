#include "VertexProcessor.h"
#include "const.h"
#include "MathHelper.h"

VertexProcessor::VertexProcessor() {

	obj2World.identity();
	world2View.identity();
	view2Proj.identity();

	rotMat.identity();
	scaleMat.identity();
	transMat.identity();

}

void VertexProcessor::setPerspective(float fovy, float aspect, float near, float far)
{
	fovy *= PI / 360;
	float f = cos(fovy) / sin(fovy);
	
	view2Proj.columns[0] = vec4f(f / aspect, 0, 0, 0); //TODO: []operator
	view2Proj.columns[1] = vec4f(0, f, 0, 0);
	view2Proj.columns[2] = vec4f(0, 0, (far + near) / (near - far), -1);
	view2Proj.columns[3] = vec4f(0, 0, 2 * far * near / (near - far), 0);


}

void VertexProcessor::setLookAt(vec3f eye, vec3f center, vec3f up)
{
	vec3f f = center - eye;
	f.normalize();
	eyePos = f;
	up.normalize();
	vec3f s = f.cross(up);
	vec3f u = s.cross(f);
	world2View.columns[0] = vec4f(s[0], u[0], -f[0], 0);
	world2View.columns[1] = vec4f(s[1], u[1], -f[1], 0);
	world2View.columns[2] = vec4f(s[2], u[2], -f[2], 0);
	world2View.columns[3] = vec4f(0, 0, 0, 1);
	Mat4x4 m;
	m.identity();
	vec4f negEye = vec4f(-eye, 1);
	m.columns[3] = negEye; //FIX: m[3] does not become -eye
	world2View = world2View * m;

}

void VertexProcessor::clear() {

	obj2World.identity();
	world2View.identity();
	view2Proj.identity();
	rotMat.identity();
	scaleMat.identity();
	transMat.identity();
	eyePos = vec3f(0, 0, 0);

}

void VertexProcessor::translate(vec3f v) {
	Mat4x4 m(
		vec4f(1, 0, 0, 0),
		vec4f(0, 1, 0, 0),
		vec4f(0, 0, 1, 0),
		vec4f(v.x, v.y, v.z, 1));
	transMat = m;
	obj2World = m * obj2World;
}

void VertexProcessor::scale(vec3f v) {
	Mat4x4 m(
		vec4f(v.x, 0, 0, 0),
		vec4f(0, v.y, 0, 0),
		vec4f(0, 0, v.z, 0),
		vec4f(0, 0, 0, 1));
	scaleMat = m;
	obj2World = m * obj2World;
}

void VertexProcessor::rotate(float a, vec3f v) {

	float s = sin(a * PI / 180), c = cos(a * PI / 180);
	v.normalize();
	Mat4x4 m(
		vec4f(v.x*v.x*(1-c) + c, v.y*v.x*(1-c) + v.z*s,
			v.x*v.z*(1-c)-v.y*s, 0),
		vec4f(v.x*v.y*(1-c)-v.z*s, v.y*v.y*(1-c) + c,
			v.y*v.z*(1-c) + v.x*s, 0),
		vec4f(v.x*v.z*(1-c) + v.y*s, v.y*v.z*(1-c)-v.x*s,
			v.z*v.z*(1-c) + c, 0),
		vec4f(0, 0, 0, 1));

	Mat4x4 tmp;
	tmp.identity();
	rotMat = m * tmp;

	obj2World = m * obj2World;

	rotMat.write();
	obj2World.write();

}

vec3f VertexProcessor::process(vec3f& v) {

	vec3f ret;

	vec4f tmp = obj2World * v;
	tmp = world2View * tmp;
	tmp = view2Proj * tmp;

	ret.x = tmp.x / tmp.w;

	ret.y = tmp.y / tmp.w;

	ret.z = tmp.z / tmp.w;

	return ret;

}

unsigned int VertexProcessor::calculateDirLight(vec3f& v, vec3f& n, Light& l)
{
	vec4f tmp = rotMat * n;
	vec3f worldSpaceNormal = vec3f(tmp.x, tmp.y, tmp.z);
	worldSpaceNormal.normalize();

	tmp = rotMat * v;
	vec3f worldSpacePosition = vec3f(tmp.x, tmp.y, tmp.z);

	float intensity = std::max(worldSpaceNormal.dot(-l.position), 0.0f);

	vec3f color = l.diffuse * intensity;

	color = color.max(l.ambient);

	color.x = color.x > 255 ? 255 : color.x < 0 ? 0 : color.x;
	color.y = color.y > 255 ? 255 : color.y < 0 ? 0 : color.y;
	color.z = color.z > 255 ? 255 : color.z < 0 ? 0 : color.z;

	return hexFromRgb(color);
}

unsigned int VertexProcessor::calculatePointLight(vec3f& v, vec3f& n, Light& l)
{
	vec4f tmp = rotMat * n;
	vec3f worldSpaceNormal = vec3f(tmp.x, tmp.y, tmp.z);
	worldSpaceNormal.normalize();

	tmp = obj2World * v;
	vec3f worldSpacePosition = vec3f(tmp.x, tmp.y, tmp.z);

	vec3f lightDir = l.position - worldSpacePosition;

	float intensity = std::max(worldSpaceNormal.dot(lightDir), 0.0f);

	vec3f spec = vec3f(0, 0, 0);

	if (intensity > 0.0) {

		lightDir.normalize();
		vec3f h = lightDir + eyePos;
		h.normalize();

		float intSpec = std::max(h.dot(n), 0.0f);
		spec = l.specular * pow(intSpec, l.shininess);

		spec.x = spec.x > 255 ? 255 : spec.x < 0 ? 0 : spec.x;
		spec.y = spec.y > 255 ? 255 : spec.y < 0 ? 0 : spec.y;
		spec.z = spec.z > 255 ? 255 : spec.z < 0 ? 0 : spec.z;
	}

	vec3f color = l.diffuse * intensity + spec;

	color = color.max(l.ambient);
	
	color.x = color.x > 255 ? 255 : color.x < 0 ? 0 : color.x;
	color.y = color.y > 255 ? 255 : color.y < 0 ? 0 : color.y;
	color.z = color.z > 255 ? 255 : color.z < 0 ? 0 : color.z;
	
	return hexFromRgb(color);
}