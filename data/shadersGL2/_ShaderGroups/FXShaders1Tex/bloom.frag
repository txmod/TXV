#version 120  
      
    // define our varying texture coordinates   
    varying vec2 v_texCoord0;
    uniform sampler2DRect tex0;
    uniform float bloom;  // range 0-1
      
      
    void main()  
    {  
        vec4 sum, dry;   
        int i, j;    
          
        for( i = -3 ;i <= 3; i++)    
        {    
            for (j = -3; j <= 3; j++)    
            {    
                sum += texture2DRect(tex0, v_texCoord0  + vec2(j, i) * 2.0) * 0.25;  // 2.0 = "radius step"
            }    
        }    
          
        sum = sum * sum * 0.012; // 0.012 = arbitrary value   
        dry = texture2DRect(tex0, v_texCoord0);
        gl_FragColor = bloom * (1.0 - ((1.0 - sum) * (1.0 - dry))) +  ((1.0 - bloom) * dry); // screen mode blending  
       
    }