#include "CubeBuilder.h"

void CubeBuilder::loadVertices(std::uint8_t flags, std::vector<Vertex>& vertices, 
	std::array<glm::vec2, 6> tex, float res)
{
	for (int i = 0; i < 6; i++)
	{
		if ((flags & (1 << i)))
			loadFace(vertices, {
			tex[0], tex[1], tex[2],
			tex[3], tex[4], tex[5],
				}, res, static_cast<CubeBuilder::Face>(1 << i));
	}


}

void CubeBuilder::loadFace(std::vector<Vertex>& vertices,
	std::array<glm::vec2, 6> tex, float res, CubeBuilder::Face face)
{

	switch (face)
	{
	case CubeBuilder::Face::BACK:
		vertices.insert(vertices.end(),
			{
				{ {-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {tex[0].x,		tex[0].y}		},
				{ { 0.5f,  0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {tex[0].x + res,	tex[0].y + res}	},
				{ { 0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {tex[0].x + res,	tex[0].y}		},
				{ { 0.5f,  0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {tex[0].x + res,	tex[0].y + res}	},
				{ {-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {tex[0].x,		tex[0].y}		},
				{ {-0.5f,  0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {tex[0].x,		tex[0].y + res}	} 
			});
		break;
	case CubeBuilder::Face::FRONT:
		vertices.insert(vertices.end(),
			{
				{ {-0.5f, -0.5f,  0.5f}, {0.0f, 0.0f, 1.0f},  {tex[1].x,		tex[1].y}		},
				{ { 0.5f, -0.5f,  0.5f}, {0.0f, 0.0f, 1.0f},  {tex[1].x + res,	tex[1].y}		},
				{ { 0.5f,  0.5f,  0.5f}, {0.0f, 0.0f, 1.0f},  {tex[1].x + res,	tex[1].y + res}	},
				{ { 0.5f,  0.5f,  0.5f}, {0.0f, 0.0f, 1.0f},  {tex[1].x + res,	tex[1].y + res}	},
				{ {-0.5f,  0.5f,  0.5f}, {0.0f, 0.0f, 1.0f},  {tex[1].x,		tex[1].y + res}	},
				{ {-0.5f, -0.5f,  0.5f}, {0.0f, 0.0f, 1.0f},  {tex[1].x,		tex[1].y}		}
			});
		break;
	case CubeBuilder::Face::LEFT:
		vertices.insert(vertices.end(),
			{
				{ {-0.5f,  0.5f,  0.5f}, {-1.0f, 0.0f, 0.0f}, {tex[2].x,		tex[2].y + res}	},
				{ {-0.5f,  0.5f, -0.5f}, {-1.0f, 0.0f, 0.0f}, {tex[2].x + res,	tex[2].y + res}	},
				{ {-0.5f, -0.5f, -0.5f}, {-1.0f, 0.0f, 0.0f}, {tex[2].x + res,	tex[2].y}		},
				{ {-0.5f, -0.5f, -0.5f}, {-1.0f, 0.0f, 0.0f}, {tex[2].x + res,	tex[2].y}		},
				{ {-0.5f, -0.5f,  0.5f}, {-1.0f, 0.0f, 0.0f}, {tex[2].x,		tex[2].y}		},
				{ {-0.5f,  0.5f,  0.5f}, {-1.0f, 0.0f, 0.0f}, {tex[2].x,		tex[2].y + res}	} 
			});

		break;
	case CubeBuilder::Face::RIGHT:
		vertices.insert(vertices.end(),
			{
				{ { 0.5f,  0.5f,  0.5f}, { 1.0f, 0.0f, 0.0f}, {tex[3].x,		tex[3].y + res}	},
				{ { 0.5f, -0.5f, -0.5f}, { 1.0f, 0.0f, 0.0f}, {tex[3].x + res,	tex[3].y}		},
				{ { 0.5f,  0.5f, -0.5f}, { 1.0f, 0.0f, 0.0f}, {tex[3].x + res,	tex[3].y + res}	},
				{ { 0.5f, -0.5f, -0.5f}, { 1.0f, 0.0f, 0.0f}, {tex[3].x + res,	tex[3].y}		},
				{ { 0.5f,  0.5f,  0.5f}, { 1.0f, 0.0f, 0.0f}, {tex[3].x,		tex[3].y + res}	},
				{ { 0.5f, -0.5f,  0.5f}, { 1.0f, 0.0f, 0.0f}, {tex[3].x,		tex[3].y}		} 
			});

		break;
	case CubeBuilder::Face::TOP:
		vertices.insert(vertices.end(),
			{
				{ {-0.5f,  0.5f, -0.5f}, {0.0f, 1.0f, 0.0f},  {tex[5].x,		tex[5].y + res}	},
				{ { 0.5f,  0.5f,  0.5f}, {0.0f, 1.0f, 0.0f},  {tex[5].x + res,	tex[5].y}		},
				{ { 0.5f,  0.5f, -0.5f}, {0.0f, 1.0f, 0.0f},  {tex[5].x + res,	tex[5].y + res}	},
				{ { 0.5f,  0.5f,  0.5f}, {0.0f, 1.0f, 0.0f},  {tex[5].x + res,	tex[5].y}		},
				{ {-0.5f,  0.5f, -0.5f}, {0.0f, 1.0f, 0.0f},  {tex[5].x,		tex[5].y + res}	},
				{ {-0.5f,  0.5f,  0.5f}, {0.0f, 1.0f, 0.0f},  {tex[5].x,		tex[5].y}		} 
			});

		break;
	case CubeBuilder::Face::BOTTOM:
		vertices.insert(vertices.end(),
			{
				{ {-0.5f, -0.5f, -0.5f}, {0.0f, -1.0f, 0.0f}, {tex[4].x,		tex[4].y + res}	},
				{ { 0.5f, -0.5f, -0.5f}, {0.0f, -1.0f, 0.0f}, {tex[4].x + res,	tex[4].y + res}	},
				{ { 0.5f, -0.5f,  0.5f}, {0.0f, -1.0f, 0.0f}, {tex[4].x + res,	tex[4].y}		},
				{ { 0.5f, -0.5f,  0.5f}, {0.0f, -1.0f, 0.0f}, {tex[4].x + res,	tex[4].y}		},
				{ {-0.5f, -0.5f,  0.5f}, {0.0f, -1.0f, 0.0f}, {tex[4].x,		tex[4].y}		},
				{ {-0.5f, -0.5f, -0.5f}, {0.0f, -1.0f, 0.0f}, {tex[4].x,		tex[4].y + res}	}
			});

		break;
	}
}

