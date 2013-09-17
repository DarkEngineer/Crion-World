#include "Landscape.h"

Landscape::Landscape()
	:
	m_width(64),
	m_height(64),
	m_numVertices(40),
	m_stepSize((m_width * m_height) * (1/pow(2, m_numVertices)))
{}