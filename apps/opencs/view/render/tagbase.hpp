#ifndef OPENCS_VIEW_TAGBASE_H
#define OPENCS_VIEW_TAGBASE_H

#include <osg/Referenced>

#include "elements.hpp"

namespace CSVRender
{
    class TagBase : public osg::Referenced
    {
            Elements mElement;

        public:

            TagBase (Elements element);

            Elements getElement() const;
    };
}

#endif
