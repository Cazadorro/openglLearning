//
// Created by Shae Bolt on 2/1/2018.
//

#ifndef GRIDMAPDISPLAY_NOISEGENUTILS_H
#define GRIDMAPDISPLAY_NOISEGENUTILS_H


#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

float ** createMesh(int width, int height);
unsigned char *createTextureMemory(int width, int height);
void accumTextureVals(int i, int j, int width, unsigned char* temp_texture, double d_noise);

template<typename OctaveNoise_T>
double accumulateNoise(int min_oct, int max_oct, int i, int j, OctaveNoise_T& temp_1){
//   static OctaveNoise<ValueFixedValueContributor<MurmurHash3>, ease::perlin, interp::linear>
//            temp_1{ValueFixedValueContributor<MurmurHash3>(1)};
    double d_noise = 0;
    for(int oct = min_oct; oct <= max_oct; oct++){
        d_noise+= temp_1.noise(j/32.0f*(1<<oct), i/32.0f*(1<<oct))/(1<<oct);
    }
    return d_noise;
}
void mainfunc(int width, int height, unsigned char* temp_texture, std::vector<float>& verticies, const glm::vec3 scale);
void genindicies(int width, int height, std::vector<int>& indices);

#endif //GRIDMAPDISPLAY_NOISEGENUTILS_H
