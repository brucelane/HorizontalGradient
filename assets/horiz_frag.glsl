#version 110

// we will use two 2D textures
uniform sampler2D tex0;
uniform sampler2D tex1;
uniform vec3      iResolution;           // viewport resolution (in pixels)
uniform float     iGlobalTime;           // shader playback time (in seconds)

// noise & fbm by iq

float hash( float n )
{
    return fract( sin(n)* 43758.5453123 );
}

float noise1( float x )
{
    float p = floor(x);
    float f = fract(x);

    f = f*f*(3.0-2.0*f);

    return mix( hash(p+0.0), hash(p+1.0), f );
}

float fbm( float p )
{
    float f = 0.0;

    f += 0.5000*noise1( p ); p = p*2.02;
    f += 0.2500*noise1( p ); p = p*2.03;
    f += 0.1250*noise1( p ); p = p*2.01;
    f += 0.0625*noise1( p );

    return f/0.9375;
}

void main(void)
{
	// using the interpolated texture coordinate, 
	// find the color of the bottom image
	//vec4 color0 = texture2D( tex0, gl_TexCoord[0].st );
	// do the same for the top image
	// vec4 color1 = texture2D( tex1, gl_TexCoord[0].st );

	// in this example, we will invert the bottom color 
	// (black becomes white, red becomes cyan, etc.)
	// color0.rgb = vec3(1.0) - color0.rgb;

	// and we will make the top image 50% transparent
	// color1.a = 0.5;

	// now, we will have to do the blending ourselves
	// vec4 result = mix(color0, color1, color1.a);

	// and set the final pixel color
	// gl_FragColor.rgb = result.rgb;
	// gl_FragColor.a = 1.0;

	vec2 uv = gl_FragCoord.xy / iResolution.xy;
	
	float c = dot( vec3( fbm( uv.y * 5.134 + iGlobalTime * 2.013 ),
			             fbm( uv.y * 15.002 + iGlobalTime * 3.591 ),
						 fbm( uv.y * 25.922 + iGlobalTime * 4.277 ) ),
				   vec3( .85, .35, .17 ) );

	gl_FragColor = vec4( c, c, c, 1.);

}