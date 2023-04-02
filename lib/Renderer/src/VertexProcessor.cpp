#include "VertexProcessor.h"
#include "const.h"
#include "MathHelper.h"

VertexProcessor::VertexProcessor() {

	obj2World.identity();
	world2View.identity();
	view2Proj.identity();

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

}

void VertexProcessor::translate(vec3f v) {
	Mat4x4 m(
		vec4f(1, 0, 0, 0),
		vec4f(0, 1, 0, 0),
		vec4f(0, 0, 1, 0),
		vec4f(v.x, v.y, v.z, 1));
	obj2World = m * obj2World;
}

void VertexProcessor::scale(vec3f v) {
	Mat4x4 m(
		vec4f(v.x, 0, 0, 0),
		vec4f(0, v.y, 0, 0),
		vec4f(0, 0, v.z, 0),
		vec4f(0, 0, 0, 1));
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
	obj2World = m * obj2World;

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
	vec4f tmp = obj2World * n;
	vec3f worldSpaceNormal = vec3f(tmp.x, tmp.y, tmp.z);
	worldSpaceNormal.normalize();

	worldSpaceNormal = n;

	printf("\n %f %f %f", worldSpaceNormal.x, worldSpaceNormal.y, worldSpaceNormal.z);

	float intensity = std::max(worldSpaceNormal.dot(-l.position), 0.0f);

	/*
	vec3f spec(0, 0, 0);

	if (intensity > 0.0f) {
		vec4f tmpWorldVertex = obj2World * v;
		vec3f worldVertex = vec3f(tmpWorldVertex.x, tmpWorldVertex.y, tmpWorldVertex.z);
		vec3f eye = -worldVertex;
		eye.normalize();
		vec3f h = l.position + eye;
		h.normalize();

		float intSpec = std::max(h.dot(worldSpaceNormal), 0.0f);
		spec = l.specular * pow(intSpec, l.shininess);
	}
	*/

	vec3f color = l.diffuse * intensity;// +spec;

	color = color.max(l.ambient);

	return hexFromRgb(color);
}

unsigned int VertexProcessor::calculatePointLight(vec3f& v, vec3f& n, Light& l)
{
	vec4f tmp = obj2World * n;
	vec3f worldSpaceNormal = vec3f(tmp.x, tmp.y, tmp.z);
	worldSpaceNormal.normalize();

	worldSpaceNormal = n;

	printf("\n %f %f %f", worldSpaceNormal.x, worldSpaceNormal.y, worldSpaceNormal.z);

	vec3f lightDir = l.position - v;


	float intensity = std::max(worldSpaceNormal.dot(lightDir), 0.0f);

	vec3f color = l.diffuse * intensity;

	color = color.max(l.ambient);

	return hexFromRgb(color);
}