/***********************************************************************
 
 This class is for drawing a fluidsolver using the OpenFrameworks texture
 
 ************************************************************************/

#pragma once

#include "MSACore.h"
#include "MSAFluidSolver.h"

namespace msa {
	namespace fluid {
        
        typedef enum {
            kDrawColor,
            kDrawMotion,
            kDrawSpeed,
            kDrawVectors,
            kDrawCount
        } DrawMode;
        
        
        vector<string>& getDrawModeTitles();
        
        class DrawerBase
#ifdef MSA_HOST_OPENFRAMEWORKS
        : public ofBaseDraws
#endif
        {
        public:
            bool	enabled;
            bool	doInvert;
            bool	useAdditiveBlending;
            float	brightness;
            float	velDrawThreshold;
            float	velDrawMult;
            int		vectorSkipCount;
            
            DrawMode		drawMode;
            
            DrawerBase();
            virtual ~DrawerBase();
            
            Solver* setup(int NX = FLUID_DEFAULT_NX, int NY = FLUID_DEFAULT_NY);
            Solver* setup(Solver* f);
            Solver* getFluidSolver();
            
            void enableAlpha(bool b);
            
            void update();
            
            void draw(float x, float y) const override;
            void draw(float x, float y, float renderWidth, float renderHeight) const override;				// this one does chooses one of the below based on drawmode
            void drawColor(float x, float y, float renderWidth, float renderHeight, bool withAlpha = false) const;
            void drawMotion(float x, float y, float renderWidth, float renderHeight, bool withAlpha = false) const;
            void drawSpeed(float x, float y, float renderWidth, float renderHeight, bool withAlpha = false) const;
            void drawVectors(float x, float y, float renderWidth, float renderHeight) const;
            void reset();
            
           // float getWidth() const override {}
            //float getHeight() const override {}
            
            void setDrawMode(DrawMode newDrawMode);
            void incDrawMode();
            void decDrawMode();
            DrawMode getDrawMode();
            string getDrawModeName();
            
        protected:
            unsigned char		*_pixels;						// pixels array to be drawn
            
            int					_glType;						// GL_RGB or GL_RGBA
            bool				_alphaEnabled;
            int					_bpp;							// 3 or 4
            
            Solver              *_fluidSolver;
            bool				_didICreateTheFluid;    // TODO: replace with shared pointer
            
            void				allocatePixels();
            
            virtual void		createTexture() = 0;									// override to create a texture
            virtual void		updateTexture() const = 0;									// override to update the texture from the pixels array
            virtual void		deleteTexture() = 0;									// override to delete the texture
            virtual void		drawTexture(float x, float y, float w, float h) const = 0;	// override to draw texture
            
            void				deleteFluidSolver();
            bool				isFluidReady();
            
        };
    }
}
