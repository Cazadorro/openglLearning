//
// Created by Shae Bolt on 12/16/2017.
//

#ifndef GRIDMAPDISPLAY_FILESYSTEM_H
#define GRIDMAPDISPLAY_FILESYSTEM_H


#include <string>


namespace filesys {
    std::string const &getRoot();

    std::string getPathFromRoot(const std::string &path);

    std::string getPathFromBin(const std::string &path);
}

#endif //GRIDMAPDISPLAY_FILESYSTEM_H
