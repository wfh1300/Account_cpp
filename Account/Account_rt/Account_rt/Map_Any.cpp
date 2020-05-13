#include "Map_Any.h"
MapAny::MapAny(const MapAny& m) :m_params(m.m_params) {}

MapAny& MapAny::operator=(const MapAny& rhs) {
	if (this == &rhs) {
		return *this;
	}
	this->m_params = rhs.m_params;
	return *this;
}
