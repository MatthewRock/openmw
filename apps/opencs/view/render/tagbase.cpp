
#include "tagbase.hpp"

CSVRender::TagBase::TagBase (Elements element) : mElement (element) {}

CSVRender::Elements CSVRender::TagBase::getElement() const
{
    return mElement;
}
