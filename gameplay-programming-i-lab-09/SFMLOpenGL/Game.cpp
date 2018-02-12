#include <Game.h>

static bool flip;

Game::Game() : window(VideoMode(800, 600), "OpenGL Cube VBO")
{
	newmat.setA11(1);
	newmat.setA12(1);
	newmat.setA13(1);

	newmat.setA21(1);
	newmat.setA22(1);
	newmat.setA23(1);

	newmat.setA31(1);
	newmat.setA32(1);
	newmat.setA33(1);

	bottomLeft.setX(-0.5f);
	bottomLeft.setY(-0.5f);
	bottomLeft.setZ(0.0f);

	topLeft.setX(-0.5f);
	topLeft.setY(0.5f);
	topLeft.setZ(0.0f);

	topRight.setX(0.5f);
	topRight.setY(0.5f);
	topRight.setZ(0.0f);

	bottomRight.setX(0.5f);
	bottomRight.setY(-0.5f);
	bottomRight.setZ(0.0f);



}

Game::~Game() {}

void Game::run()
{

	initialize();

	Event event;

	while (isRunning) {

		cout << "Game running..." << endl;

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				isRunning = false;
			}
		}
		update();
		render();
	}

}

typedef struct
{
	float coordinate[3];
	float color[3];
} Vertex;

Vertex vertex[6];
GLubyte triangles[6];

/* Variable to hold the VBO identifier */
GLuint vbo[1];
GLuint index;

void Game::initialize()
{
	isRunning = true;

	glewInit();

	/* Vertices counter-clockwise winding */

	vertex[0].coordinate[0] = bottomLeft.getX();
	vertex[0].coordinate[1] = bottomLeft.getY();
	vertex[0].coordinate[2] = bottomLeft.getZ();

	vertex[1].coordinate[0] = topLeft.getX();
	vertex[1].coordinate[1] = topLeft.getY();
	vertex[1].coordinate[2] = topLeft.getZ();

	vertex[2].coordinate[0] = topRight.getX();
	vertex[2].coordinate[1] = topRight.getY();
	vertex[2].coordinate[2] = topRight.getZ();

	vertex[3].coordinate[0] = topRight.getX(); 
	vertex[3].coordinate[1] = topRight.getY();  
	vertex[3].coordinate[2] = topRight.getZ();

	vertex[4].coordinate[0] = bottomRight.getX(); 
	vertex[4].coordinate[1] = bottomRight.getY();  
	vertex[4].coordinate[2] = bottomRight.getZ();

	vertex[5].coordinate[0] = bottomLeft.getX(); 
	vertex[5].coordinate[1] = bottomLeft.getY();  
	vertex[5].coordinate[2] = bottomLeft.getZ();

	vertex[0].color[0] = 0.1f;
	vertex[0].color[1] = 1.0f;
	vertex[0].color[2] = 0.0f;

	vertex[1].color[0] = 0.2f;
	vertex[1].color[1] = 1.0f;
	vertex[1].color[2] = 0.0f;

	vertex[2].color[0] = 0.3f;
	vertex[2].color[1] = 1.0f;
	vertex[2].color[2] = 0.0f;

	vertex[3].color[0] = 0.4f;
	vertex[3].color[1] = 1.0f;
	vertex[3].color[2] = 0.0f;

	vertex[4].color[0] = 0.5f;
	vertex[4].color[1] = 1.0f;
	vertex[4].color[2] = 0.0f;

	vertex[5].color[0] = 0.6f;
	vertex[5].color[1] = 1.0f;
	vertex[5].color[2] = 0.0f;


	triangles[0] = 0;   triangles[1] = 1;   triangles[2] = 2;
	triangles[3] = 3;   triangles[4] = 4;   triangles[5] = 5;

	/* Create a new VBO using VBO id */
	glGenBuffers(1, vbo);

	/* Bind the VBO */
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);

	/* Upload vertex data to GPU */
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 6, vertex, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &index);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLubyte) * 6, triangles, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Game::update()
{
	elapsed = clock.getElapsedTime();

	if (elapsed.asSeconds() >= 1.0f)
	{
		clock.restart();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::T))
	{
		topLeft = newmat.Translate(2, 2) * topLeft;
		bottomLeft = newmat.Translate(2, 2) * bottomLeft;
		topRight = newmat.Translate(2, 2) * topRight;
		bottomRight = newmat.Translate(2, 2) * bottomRight;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		topLeft = newmat.Scale3D(1) * topLeft;
		bottomLeft = newmat.Scale3D(1) * bottomLeft;
		topRight = newmat.Scale3D(1) * topRight;
		bottomRight = newmat.Scale3D(1) * bottomRight;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
	{
		topLeft = newmat.Rotation(1) * topLeft;
		bottomLeft = newmat.Rotation(1) * bottomLeft;
		topRight = newmat.Rotation(1) * topRight;
		bottomRight = newmat.Rotation(1) * bottomRight;
	}
	vertex[0].coordinate[0] = bottomLeft.getX();
	vertex[0].coordinate[1] = bottomLeft.getY();
	vertex[0].coordinate[2] = bottomLeft.getZ();

	vertex[1].coordinate[0] = topLeft.getX();
	vertex[1].coordinate[1] = topLeft.getY();
	vertex[1].coordinate[2] = topLeft.getZ();

	vertex[2].coordinate[0] = topRight.getX();
	vertex[2].coordinate[1] = topRight.getY();
	vertex[2].coordinate[2] = topRight.getZ();

	vertex[3].coordinate[0] = topRight.getX();
	vertex[3].coordinate[1] = topRight.getY();
	vertex[3].coordinate[2] = topRight.getZ();

	vertex[4].coordinate[0] = bottomRight.getX();
	vertex[4].coordinate[1] = bottomRight.getY();
	vertex[4].coordinate[2] = bottomRight.getZ();

	vertex[5].coordinate[0] = bottomLeft.getX();
	vertex[5].coordinate[1] = bottomLeft.getY();
	vertex[5].coordinate[2] = bottomLeft.getZ();

	cout << "Update up" << endl;
}

void Game::render()
{
	cout << "Drawing" << endl;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index);

	/*	As the data positions will be updated by the this program on the
		CPU bind the updated data to the GPU for drawing	*/
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 6, vertex, GL_STATIC_DRAW);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);


	glColorPointer(3, GL_FLOAT, sizeof(Vertex), (char*)NULL + 12);

	/*	Draw Triangle from VBO	(set where to start from as VBO can contain 
		model compoents that are and are not to be drawn )	*/
	glVertexPointer(3, GL_FLOAT, sizeof(Vertex), (char*)NULL + 0);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, (char*)NULL + 0);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);

	window.display();

}

void Game::unload()
{
	cout << "Cleaning up" << endl;

	glDeleteBuffers(1, vbo);
}

