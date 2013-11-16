#ifndef Crion_h
#define Crion_h

//namespace with necessary functions
namespace Crion
{
	struct Vertex
	{
		float x;
		float y;
		float z;

		Vertex::Vertex();
		Vertex::~Vertex();
		Vertex::Vertex(float & x, float & y, float & z);
	};
};

#endif