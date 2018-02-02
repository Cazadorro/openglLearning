//
// Created by Shae Bolt on 2/1/2018.
//

#include <cmath>
#include "noisegenutils.h"
#include "noise/ease_functions.h"
#include "noise/interpolation_functions.h"
#include "noise/murmurhash3.h"
#include "noise/WorleyNoiseContributor.h"
#include "noise/OctaveNoise.h"

float ** createMesh(int width, int height){
    float ** squares = new float*[width * height];
    for (int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            float * temp = new float[12];
            temp[0] = j;
            temp[1] = i;
            temp[2] = 1;
            temp[3] = j+1;
            temp[4] = i;
            temp[5] = 1;
            temp[6] = j;
            temp[7] = i+1;
            temp[8] = 1;
            temp[9] = j+1;
            temp[10] = i+1;
            temp[11] = 1;
            squares[j + (i*width)] = temp;
        }
    }
    return squares;
}


unsigned char *createTextureMemory(int width, int height){
    return new unsigned char[width*height * 4];
}

void accumTextureVals(int i, int j, int width, unsigned char* temp_texture, double d_noise){
    uint8_t noise = static_cast<uint8_t>(rint(d_noise));
    temp_texture[j*4 + (i * width * 4) + 0] = (noise);
    temp_texture[j*4 + (i * width * 4) + 1] = (noise);
    temp_texture[j*4 + (i * width * 4) + 2] = (noise);
    temp_texture[j*4 + (i * width * 4) + 3] = (255);
}


void mainfunc(int width, int height, unsigned char* temp_texture, std::vector<float>& verticies, const glm::vec3 scale){
//    OctaveNoise<GradientFixed4Contributor<MurmurHash3>, ease::perlin, interp::linear>
//        temp_1{GradientFixed4Contributor<MurmurHash3>(1)};
//    OctaveNoise<ValueFixedValueContributor<MurmurHash3>, ease::perlin, interp::linear>
//            temp_1{ValueFixedValueContributor<MurmurHash3>(1)};

//    OctaveNoise<GradientGenContributor<MurmurHash3>, ease::perlin, interp::linearFast>
//            temp_1{GradientGenContributor<MurmurHash3>(1)};
//    OctaveNoise<GradientTrigContributor<MurmurHash3>, ease::perlin, interp::linearFast>
//            temp_1{GradientTrigContributor<MurmurHash3>(1)};

    noise::OctaveNoise<noise::WorleyNoiseContributor<noise::MurmurHash3>, noise::ease::perlin, noise::interp::linearFast>
            temp_1{noise::WorleyNoiseContributor<noise::MurmurHash3>(1)};
//    OctaveNoise<GradientGenContributor<MurmurHash3>, ease::perlin, interp::linear>
//            temp_2{GradientGenContributor<MurmurHash3>(1)};
//    OctaveNoise<ValueFixedValueContributor<MurmurHash3>, ease::perlin, interp::linear>
//            temp_3{ValueFixedValueContributor<MurmurHash3>(1)};
//    OctaveNoise<ValueFixedValueContributor<MurmurHash3>, ease::perlin, interp::linearFast>
//            temp_4{ValueFixedValueContributor<MurmurHash3>(1)};
    int max_oct = 0;
    int min_oct = 0;
    for( int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            double d_noise = 0;
//            if(j%2 == 0){
//                d_noise += accumulateNoise(min_oct, max_oct, i, j, temp_4);
//            }
//            else{
//                d_noise += accumulateNoise(min_oct, max_oct, i, j, temp_3);
//            }
            d_noise += accumulateNoise(min_oct, max_oct, i, j, temp_1);


            d_noise*= 0.5;
            accumTextureVals(i, j, width, temp_texture, d_noise);
            verticies.push_back(float(j)*scale.x); // x
            verticies.push_back(float(d_noise)*scale.z); // y
            verticies.push_back(float(i)*scale.y); // z

        }
    }
}

void genindicies(int width, int height, std::vector<int>& indices){
    bool first = true;
    for( int y = 0; y < height-1; y++) {
        indices.push_back(y * width);
        indices.push_back(y * width);
        for (int x = 0; x < (width-1);  x++) {
            indices.push_back(x+((y+1)*width));
            indices.push_back(x+1+(y*width));
        }
        indices.push_back((width-1) + ((y+1) * width));
        indices.push_back((width-1) + ((y+1) * width));
    }
}