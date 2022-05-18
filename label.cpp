#include "label.h"

Label::Label()
{

}

Label::Label(string annotation,vector<Pixel> edges){
    this->annotation=annotation;
    this->edges=edges;
}

const string &Label::getAnnotation() const
{
    return annotation;
}

void Label::setAnnotation(const string &newAnnotation)
{
    annotation = newAnnotation;
}

const vector<Pixel> &Label::getEdges() const
{
    return edges;
}

void Label::setEdges(const vector<Pixel> &newEdges)
{
    edges = newEdges;
}

