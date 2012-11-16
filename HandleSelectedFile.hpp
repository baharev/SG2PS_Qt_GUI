#ifndef HANDLESELECTEDFILE_HPP
#define HANDLESELECTEDFILE_HPP

#include <QString>

struct HandleSelectedFile {

    virtual void handleSelectedFile(const QString& file) = 0;

    virtual ~HandleSelectedFile() { }
};

#endif // HANDLESELECTEDFILE_HPP
