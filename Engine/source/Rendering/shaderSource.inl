/* 
   Copyright 2013 KLab Inc.

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/
	//
	// Standard Render state :
	//	- "pos_attr" 	for vertex coordinate.
	//	- "uv_attr"		for uv coordinate.
	//	- "col_attr"	for color in vertex.
	//
	//	- "texture"		is sampler name for texture 0
	//

	// ------------------------------------------------------------------
	// Color Vertex Only.
	// ------------------------------------------------------------------

	const static char s_vertColorOnly[] =
		"uniform mat4 Projection;\n"
		"attribute highp vec2 pos_attr;\n"
		"attribute lowp vec4 col_attr;\n"
		"varying lowp vec4 col_var;\n"
		"void main()\n"
		"{\n"
		"    gl_Position = Projection * vec4(pos_attr, 0.0, 1.0);\n"
		"    col_var = col_attr;\n"
		"}";

	const static char s_fragColorOnly[] =
		"varying lowp vec4 col_var;\n"
		"void main()\n"
		"{\n"
		"    gl_FragColor = col_var;\n"
		"}";
				
	// ------------------------------------------------------------------
	// Simple texturing
	// ------------------------------------------------------------------
	const static char s_vertTexture[] =
		"uniform mat4 Projection;\n"
		"attribute highp vec2 pos_attr;\n"
		"attribute mediump vec2 uv_attr;\n"
		"varying mediump vec2 uv_var;\n"
		"void main()\n"
		"{\n"
		"    gl_Position = Projection * vec4(pos_attr, 0.0, 1.0);\n"
		"	uv_var = uv_attr;\n"
		"}";

	const static char s_fragTexture[] =
		"varying mediump vec2 uv_var;\n"
		"uniform lowp sampler2D texture;\n"
		"void main()\n"
		"{\n"
		"    gl_FragColor  = texture2D(texture,uv_var);\n"
		"}";

		
		
				
	// ------------------------------------------------------------------
	// Color Vertex RGBA * Texture
	// ------------------------------------------------------------------
	
	const static char sh_vertColTexture[] =
		"uniform mat4 Projection;\n"
		"attribute highp vec2 pos_attr;\n"
		"attribute mediump vec2 uv_attr;\n"
		"attribute lowp vec4 col_attr;\n"
		"varying lowp vec4 col_var;\n"
		"varying mediump vec2 uv_var;\n"
		"void main()\n"
		"{\n"
		"    gl_Position = Projection * vec4(pos_attr, 0.0, 1.0);\n"
		"    col_var = col_attr;\n"
		"	 uv_var  = uv_attr;\n"
		"}";

	const static char sh_fragColTexture[] =
		"varying lowp vec4 col_var;\n"
		"varying mediump vec2 uv_var;\n"
		"uniform lowp sampler2D texture;\n"
		"void main()\n"
		"{\n"
		"	gl_FragColor  = texture2D(texture,uv_var) * col_var;\n"
		"}";

	// ------------------------------------------------------------------
	//   Special Shader Extension : Brightness
	// ------------------------------------------------------------------

	// float "power"
	const static char sh_brightNessVS[] =
		"uniform mat4 Projection;\n"
		"attribute highp vec2 pos_attr;\n"
		"attribute mediump vec2 uv_attr;\n"
		"attribute lowp vec4 col_attr;\n"
		"varying lowp vec4 col_var;\n"
		"varying mediump vec2 uv_var;\n"
		"uniform lowp float power;\n"
		"void main()\n"
		"{\n"
		"    gl_Position = Projection * vec4(pos_attr, 0.0, 1.0);\n"
		"    col_var = col_attr * power;\n"
		"	 uv_var  = uv_attr;\n"
		"}";
	
	// ------------------------------------------------------------------
	//   Special Shader Extension : Colorize
	// ------------------------------------------------------------------

	// float    "power"
	// float[3] "colorize"
	const static char sh_colorizePS[] = 
		"varying lowp vec4 col_var;\n"
		"varying mediump vec2 uv_var;\n"
		"uniform lowp sampler2D texture;\n"
		"uniform lowp vec3 colorize;\n"
		"uniform lowp float power;\n"
		"const lowp vec3 coef = vec3(0.2125, 0.7154, 0.0721);"
		"void main()\n"
		"{\n"
		"   lowp vec4 color     = texture2D(texture,uv_var) * col_var;\n"			// Read Texture
		"	gl_FragColor        = mix(vec4(vec3(dot(color.rgb, coef)) * colorize,color.a),color,power);\n"
		"}";

	// ------------------------------------------------------------------
	//   Special Shader Extension : Saturate
	// ------------------------------------------------------------------

	// float    "power"
	const static char sh_saturatePS[] = 
		"varying lowp vec4 col_var;\n"
		"varying mediump vec2 uv_var;\n"
		"uniform lowp sampler2D texture;\n"
		"uniform lowp float power;\n"
		"const lowp vec3 coef = vec3(0.2125, 0.7154, 0.0721);"
		"void main()\n"
		"{\n"
		"   lowp vec4 color     = texture2D(texture,uv_var) * col_var;\n"			// Read Texture
		"	gl_FragColor        = mix(vec4(vec3(dot(color.rgb, coef)),color.a),color,power);\n"
		"}";

	// ------------------------------------------------------------------
	//   Special Shader Extension : Ramp lookup
	// ------------------------------------------------------------------

	// texture    "table" : 16x1 pixel table
	const static char sh_curvePS[] = 
		"varying lowp vec4 col_var;\n"
		"varying mediump vec2 uv_var;\n"
		"uniform lowp sampler2D texture;\n"
		"uniform lowp sampler2D table;\n"
		"void main()\n"
		"{\n"
		"   lowp vec4 color     = texture2D(texture,uv_var) * col_var;\n"			// Read Texture
		"	gl_FragColor        = vec4(texture2D(table,vec2(color.r,0.0)).r , texture2D(table,vec2(color.g,0.0)).g, texture2D(table,vec2(color.b,0.0)).b, color.a);\n"
		"}";

	// ------------------------------------------------------------------
	//   Special Shader Extension : Tone mapping
	// ------------------------------------------------------------------

	const static char sh_toneVS_2D[] =
		"uniform mat4 Projection;\n"
		"attribute highp vec2 pos_attr;\n"
		"attribute mediump vec2 uv_attr;\n"
		"attribute lowp vec4 col_attr;\n"
		"varying lowp vec4 col_var;\n"
		"varying mediump vec2 uv_var;\n"
		"void main()\n"
		"{\n"
		"    gl_Position = Projection * vec4(pos_attr, 0.0, 1.0);\n"
		"    col_var = col_attr * vec4(0.06135,15.98,1.0,1.0);\n"
		"	 uv_var  = uv_attr;\n"
		"}";

	// texture	"table" : 256x16 pixel table
	const static char sh_tonePS_2D[] = 
		"varying lowp vec4 col_var;\n"
		"varying mediump vec2 uv_var;\n"
		"uniform lowp sampler2D texture;\n"
		"uniform lowp sampler2D table;\n"
		"void main()\n"
		"{\n"
		"   lowp vec4 color     = texture2D(texture,uv_var) * col_var;\n"			// Read Texture and apply vertex color
        "   gl_FragColor        = vec4(texture2D(table, vec2(color.r + (floor(color.b)/15.98),color.g)).rgb,color.a);\n"
		"}";

	const static char sh_toneVS_3D[] =
		"uniform mat4 Projection;\n"
		"attribute highp vec2 pos_attr;\n"
		"attribute mediump vec2 uv_attr;\n"
		"attribute lowp vec4 col_attr;\n"
		"varying lowp vec4 col_var;\n"
		"varying mediump vec2 uv_var;\n"
		"void main()\n"
		"{\n"
		"    gl_Position = Projection * vec4(pos_attr, 0.0, 1.0);\n"
		"    col_var = col_attr;\n"
		"	 uv_var  = uv_attr;\n"
		"}";

	// texture	"table" : 256x16 pixel table
	const static char sh_tonePS_3D[] =
		"#extension GL_OES_texture_3D : enable\n"
		"varying lowp vec4 col_var;\n"
		"varying mediump vec2 uv_var;\n"
		"uniform lowp sampler2D texture;\n"
		"uniform lowp sampler3D table;\n"
		"void main()\n"
		"{\n"
		"   lowp vec4 color     = texture2D(texture,uv_var) * col_var;\n"			// Read Texture and apply vertex color
		"   gl_FragColor        = vec4(texture3D(table, color.rgb).rgb,color.a);\n"
		"}";

	// ------------------------------------------------------------------
	//   Special Shader Extension : Mosaic (Warning : work in texture space : does not support rotation, scaling)
	// ------------------------------------------------------------------

	// float "power"
	const static char sh_mosaicVS[] =
		"uniform mat4 Projection;\n"
		"attribute highp vec2 pos_attr;\n"
		"attribute mediump vec2 uv_attr;\n"
		"attribute lowp vec4 col_attr;\n"
		"varying lowp vec4 col_var;\n"
		"varying mediump vec2 uv_var;\n"
		"uniform mediump float power;\n"
		"void main()\n"
		"{\n"
		"    gl_Position = Projection * vec4(pos_attr, 0.0, 1.0);\n"
		"    col_var = col_attr;\n"
		"	 uv_var  = uv_attr * power;\n"
		"}";
		
	// float	"power"
	const static char sh_mosaicPS[] = 
		"varying lowp vec4 col_var;\n"
		"varying mediump vec2 uv_var;\n"
		"uniform lowp sampler2D texture;\n"
		"uniform lowp sampler2D table;\n"
		"uniform mediump float power;\n"
		"void main()\n"
		"{\n"
		"	gl_FragColor        = texture2D(texture, floor(uv_var) / power) * col_var;\n"
		"}";

	// TODO film noise
	// TODO UV perturbation per pixel
	// TODO UV perturbation per vertex (grid)

