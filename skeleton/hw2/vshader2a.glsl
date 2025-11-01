#version 330

in	vec2	a_Position;	// attribute variable
uniform	mat4	u_Projection;	// uniform variable for passing projection matrix
uniform float u_Theta;        // rotation angle (degrees)
uniform bool u_Twist;         // toggle for twist effect

void main()
{
    // convert to radians
    float angle = radians(u_Theta);
    vec2 pos = a_Position;

    // base rotation values
    float c = cos(angle);
    float s = sin(angle);

    // if twist is enabled, scale angle by radius
    if (u_Twist) {
	float r = length(pos);
	float twistAngle = r * angle;
	c = cos(twistAngle);
	s = sin(twistAngle);
    }

    // apply rotation
    vec2 rotated = vec2(pos.x * c - pos.y * s, pos.x * s + pos.y * c);

    // output final vertex position
    gl_Position = u_Projection * vec4(rotated, 0.0, 1.0);
}
