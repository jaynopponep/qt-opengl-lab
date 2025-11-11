#version 330

in	vec2	a_Position;	// attribute variable: position vector
in	vec3	a_Color;	// attribute variable: color vector

out	vec4	v_Color;	// varying variable for passing color to fragment shader

uniform	mat4	u_Modelview;	// uniform variable for passing modelview  matrix
uniform	mat4	u_Projection;	// uniform variable for passing projection matrix
uniform	float	u_Theta;	// Theta parameter
uniform	int	u_Twist;	// Twist flag

void main() 
{
	// start with original vertex position
	    vec2 pos = a_Position;

	    // compute base rotation
	    float c = cos(u_Theta);
	    float s = sin(u_Theta);

	    // if twist is enabled, modify angle by radius
	    if (u_Twist == 1) {
		float r = length(pos);
		float twistAngle = r * u_Theta;
		c = cos(twistAngle);
		s = sin(twistAngle);
	    }

	    // apply rotation or twist
	    vec2 rotated = vec2(pos.x * c - pos.y * s,
	                        pos.x * s + pos.y * c);

	    // apply modelview and projection transforms
	    gl_Position = u_Projection * u_Modelview * vec4(rotated, 0.0, 1.0);

	    // pass color to fragment shader
	    v_Color = vec4(a_Color, 1.0);
}
