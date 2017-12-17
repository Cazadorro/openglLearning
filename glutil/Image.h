//
// Created by shae on 11/21/17.
//

#ifndef GRIDMAPDISPLAY_RAWIMAGE_H
#define GRIDMAPDISPLAY_RAWIMAGE_H




#include <string>
#include <glm/glm.hpp>

class Image {
    int m_width;
    int m_height;
    GLenum m_channels;
    unsigned char *m_data;

public:
    Image(unsigned char *data, int width, int height, GLenum channels);

    explicit Image(const std::string &file_location, int chosenChannels = 0);

    ~Image();

    int getWidth() const;

    int getHeight() const;

    GLenum getChannelEnum() const;

    const unsigned char *getData() const;

private:
};


#endif //GRIDMAPDISPLAY_RAWIMAGE_H
