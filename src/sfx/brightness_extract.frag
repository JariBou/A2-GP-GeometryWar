uniform sampler2D texture;

void main(){

    vec2 texel = vec2(gl_TexCoord[0]);
	vec4 pixel = vec4(texture2D(texture, texel));
	

	float brightness = dot(pixel.rgb, vec3(0.2126, 0.2152, 0.0722));
    if(pixel.r < 0.0005 && pixel.g < 0.0005 && pixel.b < 0.0005) {
		gl_FragColor = vec4(1,1,1,0);
	} else {
		gl_FragColor = pixel;
	}

}