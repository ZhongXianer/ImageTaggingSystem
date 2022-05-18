#ifndef LABEL_H
#define LABEL_H
#include <string>
#include <vector>
#include <pixel.h>

using namespace std;

class Label
{
public:
    Label();
    Label(string annotation,vector<Pixel> edges);
    const string &getAnnotation() const;
    void setAnnotation(const string &newAnnotation);

    const vector<Pixel> &getEdges() const;
    void setEdges(const vector<Pixel> &newEdges);
private:
    string annotation;
    vector<Pixel> edges;
};

#endif // LABEL_H
