#include "Spline_Z.h"

Spline_Z::Spline_Z() {
    SetGeometryType(SPLINE_Z);
    EnableFlag(FL_OBJECT_NO_SEADCOLLIDE);
    m_Length = 0.0f;
}
