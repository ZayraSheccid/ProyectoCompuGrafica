#include <iostream>
#include <cmath>

// GLEW
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// Other Libs
#include "stb_image.h"

// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//Load Models
#include "SOIL2/SOIL2.h"


// Other includes
#include "Shader.h"
#include "Camera.h"
#include "Model.h"

//spotlight direccion e iluminacion (cara) apunta desde el fragmento hasta la fuente de luz 
//directional light ambientar un espacio solo tiene una direccion (barata) 
//pointlight tiene posicion e intensidad (formula) 

// Function prototypes
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
void MouseCallback(GLFWwindow* window, double xPos, double yPos);
void DoMovement();
void animacion();
void animacion1();

// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;
int SCREEN_WIDTH, SCREEN_HEIGHT;

// Camera
Camera  camera(glm::vec3(0.0f, 0.0f, 3.0f));
GLfloat lastX = WIDTH / 2.0;
GLfloat lastY = HEIGHT / 2.0;
bool keys[1024];
bool firstMouse = true;
// Light attributes
glm::vec3 lightPos(0.0f, 0.0f, 0.0f); //posicion

bool active = false;
bool activAnim = true;
bool rotatePoke2 = false;
bool rotatePintu = false;
bool moveArb = true;
bool moveArb1 = true;
bool animacionActivada = false;
bool activePot = true;
bool moveSofa1Positive = false;
bool moveSofa1Negative = false;
bool circuito = false;
bool recorrido1 = true;
bool recorrido2 = false;
bool recorrido3 = false;
bool recorrido4 = false;
bool recorrido5 = false;
bool recorrido6 = false;
bool circuito1 = false;
bool reco1 = true;
bool reco2 = false;
bool reco3 = false;
bool reco4 = false;
float pikaSpeed = 0.01f;
float Speed = 0.001f;
float SpeedM = 0.001f;
float poke2Rotation = 0.0f;
float pokeRotation = 0.0f;
//float pikaPosX = 0.0f;
float pikaY = 0.0f;
float MewPosY = 0.0f;
float sofa1PosZ = -4.0f;
float PosX = 0.0f;
float PosXM = 0.0f;
const float sofaSpeed = 0.01f;
const float bounceSpeed = 1.5f;
const float rotationSpeed = 50.0f;
float movKitY = 0.0;
float movKitX = 0.0;
float movKitZ = 0.0;
float rotKit = 0.0f;
const float ySpeed = 0.01f;
float desplay = 0.0f;
float rotPik = 0.0f;
float movPikY = 0.0f;
float movPikX = 0.0f;
float movPikZ = 0.0f;
bool activeMew = true;
float jump = 5.0f;

//pokebola abierta-cerrada
bool activAnim1 = true; //animacion activada
float rotTile1 = 0;
bool pokeballAbierta = false;
bool n1 = false; //no permite el cambio 

//pokebola abierta-cer
bool activAnim2 = true; //animacion activada
float rotTile2 = 0;
bool pokeballAbierta2 = false;
bool n2 = false; //no permite el cambio 


glm::vec3 PosIniP(-9.5f, -0.5f, 9.0f);
glm::vec3 PosIni(1.5f, 1.15f, 4.1f);
glm::vec3 pokePosition(1.5f, 1.0f, 4.3f);
glm::vec3 LightP1;
glm::vec3 LightP2;
glm::vec3 LightP3;
glm::vec3 LightP4;
glm::vec3 LightP5;

// Positions of the point lights
glm::vec3 pointLightPositions[] = {
	glm::vec3(7.0f, 1.0f, 0.0f),
	glm::vec3(1.0f, 1.0f, -3.0f),
	glm::vec3(-4.5f, 0.0f, -4.0f),
	glm::vec3(0.0f, 18.3f, -0.12f)
};

float vertices[] = {
	 -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	   -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	   -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

	   -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
	   -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
	   -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

	   -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

	   -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	   -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	   -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

	   -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	   -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	   -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
};

// Deltatime
GLfloat deltaTime = 0.0f;	// Time between current frame and last frame
GLfloat lastFrame = 0.0f;  	// Time of last frame



int main()
{
	// Init GLFW
	glfwInit();
	// Set all the required options for GLFW
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);*/

	// Create a GLFWwindow object that we can use for GLFW's functions
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Iluminacion 2", nullptr, nullptr);

	if (nullptr == window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);

	glfwGetFramebufferSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);

	// Set the required callback functions
	glfwSetKeyCallback(window, KeyCallback);
	glfwSetCursorPosCallback(window, MouseCallback);

	// GLFW Options
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	if (GLEW_OK != glewInit())
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return EXIT_FAILURE;
	}

	// Define the viewport dimensions
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);



	Shader lightingShader("Shaders/lighting.vs", "Shaders/lighting.frag");
	Shader lampShader("Shaders/lamp.vs", "Shaders/lamp.frag");

	Model sofa((char*)"Models/Pokemon/sofaPok1.obj");
	Model sofa1((char*)"Models/Pokemon/sofaPok2.obj");
	Model mesa((char*)"Models/Pokemon/mesaRecep.obj");
	Model poke((char*)"Models/Pokemon/pokebola1.obj");
	Model pedes((char*)"Models/Pokemon/pedes.obj");
	Model pika((char*)"Models/Pokemon/pikachufanta.obj");
	Model piso((char*)"Models/Pokemon/pisoMus.obj");
	Model pedes2((char*)"Models/Pokemon/pedes2.obj");
	Model jero((char*)"Models/Pokemon/jeropok.obj");
	Model fachada((char*)"Models/Pokemon/Pokemon_center_final.obj");
	Model poke2((char*)"Models/Pokemon/poke2.obj");
	Model pintura((char*)"Models/Pokemon/pinturaPok.obj");
	Model pedes3((char*)"Models/Pokemon/pedesPok.obj");
	Model skybox((char*)"Models/Pokemon/skybox.obj");
	Model lampara((char*)"Models/Pokemon/lampara.obj");
	Model maceta((char*)"Models/Pokemon/maceta.obj");
	Model mesaext((char*)"Models/Pokemon/mesaext.obj");
	Model mew((char*)"Models/Pokemon/mew.obj");
	Model arbol((char*)"Models/Pokemon/arbol1.obj");
	Model pasto((char*)"Models/Pokemon/pasto.obj");
	Model pokebolainf((char*)"Models/Pokemon/Pokeball_abajo.obj");
	Model pokebolasup((char*)"Models/Pokemon/Pokeball_arriba.obj");
	Model charma((char*)"Models/Pokemon/charmander.obj");
	Model poke1((char*)"Models/Pokemon/poke1.obj");
	Model arcanine((char*)"Models/Pokemon/arcanine.obj");
	Model veno((char*)"Models/Pokemon/veno.obj");
	Model thun((char*)"Models/Pokemon/thun.obj");
	Model wee((char*)"Models/Pokemon/wee.obj");
	Model geo((char*)"Models/Pokemon/geo.obj");
	Model pokebosup((char*)"Models/Pokemon/Pokearr.obj");
	Model pokeboinf((char*)"Models/Pokemon/Pokeab.obj");
	Model kaka((char*)"Models/Pokemon/Kaka.obj");
	Model chari((char*)"Models/Pokemon/charizard.obj");


	// First, set the container's VAO (and VBO)
	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// Set texture units
	lightingShader.Use();


	glm::mat4 projection = glm::perspective(camera.GetZoom(), (GLfloat)SCREEN_WIDTH / (GLfloat)SCREEN_HEIGHT, 0.1f, 100.0f);

	// Game loop
	while (!glfwWindowShouldClose(window))
	{

		// Calculate deltatime of current frame
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();
		DoMovement();
		//animacion(deltaTime);
		animacion();
		animacion1();


		// Clear the colorbuffer
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// OpenGL options
		glEnable(GL_DEPTH_TEST);



		//Load Model


		// Use cooresponding shader when setting uniforms/drawing objects
		lightingShader.Use();

		glUniform1i(glGetUniformLocation(lightingShader.Program, "material.diffuse"), 0);
		glUniform1i(glGetUniformLocation(lightingShader.Program, "material.specular"), 1); //carga la especular comentar para no hacer calculos
		glUniform1f(glGetUniformLocation(lightingShader.Program, "material.shininess"), 32.0f);
		GLint viewPosLoc = glGetUniformLocation(lightingShader.Program, "viewPos");
		glUniform3f(viewPosLoc, camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);


		// Directional light
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.direction"), -0.2f, -1.0f, -0.3f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.ambient"), 0.3f, 0.3f, 0.3f); //un numero grande lo hace mas brillante 
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.diffuse"), 0.3f, 0.3f, 0.3f);//se cambia ambiental y difusa 
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.specular"), 1.0f, 1.0f, 1.0f); //aumenta la intensidad 
		//tansparencia imagenes png

		// Point light 1
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].position"), pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].ambient"), 0.05f, 0.05f, 0.05f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].diffuse"), LightP1.x, LightP1.y, LightP1.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].specular"), LightP1.x, LightP1.y, LightP1.z);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].linear"), 0.7f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].quadratic"), 1.8f);

		// Point light 2
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].position"), pointLightPositions[1].x, pointLightPositions[1].y, pointLightPositions[1].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].ambient"), 0.05f, 0.05f, 0.05f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].diffuse"), LightP2.x, LightP2.y, LightP2.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[1].specular"), LightP2.x, LightP2.y, LightP2.z);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].linear"), 0.7f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[1].quadratic"), 1.8f);

		// Point light 3
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].position"), pointLightPositions[2].x, pointLightPositions[2].y, pointLightPositions[2].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].ambient"), 0.05f, 0.05f, 0.05f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].diffuse"), LightP3.x, LightP3.y, LightP3.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[2].specular"), LightP3.x, LightP3.y, LightP3.z);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[2].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[2].linear"), 0.7f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[2].quadratic"), 1.8f);

		// Point light 4
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].position"), pointLightPositions[3].x, pointLightPositions[3].y, pointLightPositions[3].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].ambient"), 0.05f, 0.05f, 0.05f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].diffuse"), LightP4.x, LightP4.y, LightP4.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[3].specular"), LightP4.x, LightP4.y, LightP4.z);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[3].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[3].linear"), 0.027f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[3].quadratic"), 0.017f);
		

		// SpotLight posicion y direccion se da la de la camara 
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.position"), camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.direction"), camera.GetFront().x, camera.GetFront().y, camera.GetFront().z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.ambient"), 1.0f, 1.0f, 1.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.diffuse"), 1.0f, 1.0f, 1.0f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.specular"), 1.0f, 1.0f, 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.linear"), 0.35f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.quadratic"), 0.44f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.cutOff"), glm::cos(glm::radians(10.5f)));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.outerCutOff"), glm::cos(glm::radians(15.0f))); //cono interno menor al externo 

		// Set material properties
		glUniform1f(glGetUniformLocation(lightingShader.Program, "material.shininess"), 8.0f);

		// Create camera transformations
		glm::mat4 view;
		view = camera.GetViewMatrix();

		// Get the uniform locations
		GLint modelLoc = glGetUniformLocation(lightingShader.Program, "model");
		GLint viewLoc = glGetUniformLocation(lightingShader.Program, "view");
		GLint projLoc = glGetUniformLocation(lightingShader.Program, "projection");

		// Pass the matrices to the shader
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));


		glm::mat4 model(1);



		//Carga de modelo 
		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		
		//model = glm::mat4(1);
		//skybox.Draw(lightingShader);


		//fachada museo 
		model = glm::mat4(1);
		fachada.Draw(lightingShader);

		//pasto
		model = glm::mat4(1);
		pasto.Draw(lightingShader);

		//mesa recepcion
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(0.0f, 0.22f, 4.0f));
		glEnable(GL_BLEND);//Avtiva la funcionalidad para trabajar el canal alfa se pone objetos translucidos
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //operaciones de transparencia
		glUniform4f(glGetUniformLocation(lightingShader.Program, "colorAlfa"), 1.0f, 1.0f, 1.0f, 0.3f); //TRANSPARENCIA definir 
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		mesa.Draw(lightingShader);
		glDisable(GL_BLEND);  //Desactiva el canal alfa 
		

		//RECEPCION
		
		//sofa
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-13.0f, -0.5f, 3.5f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		sofa.Draw(lightingShader);

		//sofa1
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-11.0, -0.5f, sofa1PosZ));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		sofa1.Draw(lightingShader);
		
		//pokebola
		model = glm::mat4(1);
		model = glm::translate(model, PosIni + glm::vec3(movKitX, movKitY, movKitZ));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		poke.Draw(lightingShader);

		//pedestal
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(7.0f, -0.46f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		pedes.Draw(lightingShader);

		//pedes3

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(1.0f, -0.45f, -3.0f)); 
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		pedes3.Draw(lightingShader);


		//pokebola grande

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(1.0f, 2.0f, -3.0f));
		model = glm::rotate(model, glm::radians(pokeRotation), glm::vec3(0.0f, 1.0f, 0.0f)); //gira la pokebola
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		poke2.Draw(lightingShader);


		//pikachu fantasma
		model = glm::mat4(1);
		model = glm::translate(model, PosIniP + glm::vec3(movPikX, movPikY, movPikZ));
		model = glm::rotate(model, glm::radians(rotPik), glm::vec3(0.0f, 1.0f, 0.0));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		pika.Draw(lightingShader);


		//pedestal 2
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-4.5f, -0.14f, -4.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		pedes2.Draw(lightingShader);


		//jero
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-4.5f, 1.5f, -3.8f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		jero.Draw(lightingShader);


		//pintura
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(0.0f, 5.7f, -3.0f));
		model = glm::translate(model, glm::vec3(-13.9f, desplay, -3.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		pintura.Draw(lightingShader);
		
		//lampara
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(0.0f, 17.5f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		lampara.Draw(lightingShader);

		//maceta
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(11.0f, -0.47f, -6.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		maceta.Draw(lightingShader);

		//maceta
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-11.0f, -0.47f, -6.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		maceta.Draw(lightingShader);

		//EXTERIOR
		
		//mesa exterior
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(0.0f, -0.9f, -18.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		mesaext.Draw(lightingShader);


		//mew
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(0.0f, MewPosY, -20.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		mew.Draw(lightingShader);

		//mew
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(2.5f, MewPosY, -18.0f));
		model = glm::rotate(model, glm::radians(270.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		mew.Draw(lightingShader);

		//mew
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-2.5f, MewPosY, -18.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		mew.Draw(lightingShader);

		//arbol
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-28.5f, -0.9f, -26.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		arbol.Draw(lightingShader);
		
		//mimkyu
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(8.5f+PosX, -0.9f, -28.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		pika.Draw(lightingShader);

		//mew
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(8.5f+PosXM, -1.0f, -24.0f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		mew.Draw(lightingShader);

		//arbol
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(8.5f, -0.9f, -26.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		arbol.Draw(lightingShader);

		//arbol
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(28.5f, -0.9f, -26.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		arbol.Draw(lightingShader);

		//arbol
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-10.5f, -0.9f, -26.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		arbol.Draw(lightingShader);


		//SALA 2 DERECHA

		//pedestal
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(28.0f, -0.46f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		pedes.Draw(lightingShader);

		//thundurus
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(28.0f, 1.26f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		thun.Draw(lightingShader);

		//pedestal
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(20.0f, -0.46f, 5.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		pedes.Draw(lightingShader);

		//weedle
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(20.0f, 1.26f, 5.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		wee.Draw(lightingShader);


		//pedestal
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(20.0f, -0.46f, -5.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		pedes.Draw(lightingShader);

		//geodude
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(20.0f, 1.26f, -5.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		geo.Draw(lightingShader);

		//lampara
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(20.0f, 17.5f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		lampara.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(18.0f, 0.46f, 0.0f));
		model = glm::rotate(model, glm::radians(-rotTile2), glm::vec3(1.0f, 0.0f, 0.0f)); //se abre la pokebola
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//model = glm::mat4(1); //seteo de matriz
		pokebosup.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(18.0f, 0.46f, 0.0f));
		//model = glm::scale(model, glm::vec3(0.02f, 0.02f, 0.02f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		pokeboinf.Draw(lightingShader);

		
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(18.0f, 0.46f, 0.9f));
		//model = glm::scale(model, glm::vec3(0.02f, 0.02f, 0.02f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		kaka.Draw(lightingShader);



		//SALA 1 IZQUIERDA

		//pedestal
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-28.0f, -0.46f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		pedes.Draw(lightingShader);

		//pedestal
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-17.0f, -0.46f, 5.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		pedes.Draw(lightingShader);

		//pedestal
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-17.0f, -0.46f, -5.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		pedes.Draw(lightingShader);

		//pokebola abierta
		//glm::mat4 model(1);
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-22.0f, 0.46f, 0.0f));
		model = glm::rotate(model, glm::radians(-rotTile1), glm::vec3(1.0f, 0.0f, 0.0f)); //se abre la pokebola
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		//model = glm::mat4(1); //seteo de matriz
		pokebolasup.Draw(lightingShader);

		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-22.0f, 0.46f, 0.0f));
		//model = glm::scale(model, glm::vec3(0.02f, 0.02f, 0.02f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		pokebolainf.Draw(lightingShader);

		//charmander
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-22.0f, 0.46f, 0.9f));
		//model = glm::scale(model, glm::vec3(0.02f, 0.02f, 0.02f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		charma.Draw(lightingShader);

		//puff
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-17.0f, 1.26f, -5.0f));
		//model = glm::scale(model, glm::vec3(0.02f, 0.02f, 0.02f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		poke1.Draw(lightingShader);


		//golbat
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-17.0f, 1.26f, 5.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		arcanine.Draw(lightingShader);

		//venomoth
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-28.0f, 1.26f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		veno.Draw(lightingShader);

		//lampara
		model = glm::mat4(1);
		model = glm::translate(model, glm::vec3(-22.0f, 17.5f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		lampara.Draw(lightingShader);


		glBindVertexArray(0);


		// Also draw the lamp object, again binding the appropriate shader
		lampShader.Use();
		// Get location objects for the matrices on the lamp shader (these could be different on a different shader)
		modelLoc = glGetUniformLocation(lampShader.Program, "model");
		viewLoc = glGetUniformLocation(lampShader.Program, "view");
		projLoc = glGetUniformLocation(lampShader.Program, "projection");

		// Set matrices
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
		model = glm::mat4(1);
		model = glm::translate(model, lightPos);
		model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		// Draw the light object (using light's vertex attributes)
		for (GLuint i = 0; i < 4; i++)
		{
			model = glm::mat4(1);
			model = glm::translate(model, pointLightPositions[i]);
			model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
			glBindVertexArray(VAO);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		glBindVertexArray(0);



		// Swap the screen buffers
		glfwSwapBuffers(window);
	}


	// Terminate GLFW, clearing any resources allocated by GLFW.
	glfwTerminate();



	return 0;
}

// Moves/alters the camera positions based on user input
void DoMovement()
{

	// Camera controls
	if (keys[GLFW_KEY_W] || keys[GLFW_KEY_UP])
	{
		camera.ProcessKeyboard(FORWARD, deltaTime);

	}

	if (keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN])
	{
		camera.ProcessKeyboard(BACKWARD, deltaTime);


	}

	if (keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT])
	{
		camera.ProcessKeyboard(LEFT, deltaTime);


	}

	if (keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT])
	{
		camera.ProcessKeyboard(RIGHT, deltaTime);


	}

	if (keys[GLFW_KEY_T])
	{
		pointLightPositions[0].x += 0.01f;
	}
	if (keys[GLFW_KEY_G])
	{
		pointLightPositions[0].x -= 0.01f;
	}

	if (keys[GLFW_KEY_Y])
	{
		pointLightPositions[0].y += 0.01f;
	}

	if (keys[GLFW_KEY_H])
	{
		pointLightPositions[0].y -= 0.01f;
	}
	if (keys[GLFW_KEY_U])
	{
		pointLightPositions[0].z -= 0.1f;
	}
	if (keys[GLFW_KEY_J])
	{
		pointLightPositions[0].z += 0.01f;
	}

	if (activAnim && rotatePoke2) {
		pokeRotation += 1.0f; // Incrementa el valor de rotación
		if (pokeRotation >= 360.0f) {
			pokeRotation = 0.0f; // Reinicia la rotación después de 360 grados
		}
	}

	if (activeMew) {
		MewPosY += pikaSpeed;

		// Verificar límite superior
		if (MewPosY > 1.0f) {
			MewPosY = 1.0f;
			// Cambiar la dirección al alcanzar el límite superior
			pikaSpeed = -pikaSpeed;
		}
		// Verificar límite inferior
		else if (MewPosY < -0.9f) {
			MewPosY = -0.9f;
			// Cambiar la dirección al alcanzar el límite inferior
			pikaSpeed = -pikaSpeed;
		}
	}

	if (moveSofa1Positive) {
		sofa1PosZ += sofaSpeed;

		// Aplicar límite de 5 en el eje Z positivo
		if (sofa1PosZ > 1.0f) {
			sofa1PosZ = 1.0f;
			moveSofa1Positive = false;
		}
	}

	if (moveSofa1Negative) {
		sofa1PosZ -= sofaSpeed;

		// Aplicar límite de -2 en el eje Z negativo
		if (sofa1PosZ < -5.0f) {
			sofa1PosZ = -5.0f;
			moveSofa1Negative = false;
		}
	}

	if (keys[GLFW_KEY_I])
	{
		circuito = true;
	}

	if (rotatePintu) {
		desplay -= ySpeed;

		// Aplicar límite de -1.0f en el eje Y negativo
		if (desplay < 0.0f) {
			desplay = -5.2f;
			rotatePintu = false;
		}
	}

	if (keys[GLFW_KEY_9])
	{
		circuito1 = true;
	}

	if (moveArb) {
		PosX += Speed;

		if (PosX > 0.4f) {
			PosX = -0.4f;
		}
		else if (PosX < -0.4f) {
			PosX = 0.4f;
		}
	}

	if (moveArb1) {
		PosXM -= SpeedM;

		if (PosXM < -0.4f) {
			PosXM = 0.4f;
		}
		else if (PosXM > 0.4f) {
			PosXM = -0.4f;
		}
	}

	if (activAnim1 && n1) // si ambas estan encendidas
	{
		if (pokeballAbierta)
		{
			if (rotTile1 < 45.0f)
			{
				rotTile1 += 10.0f * deltaTime; // Incrementa la rotación 
			}
			else
			{
				n1 = false; // fin de la aimacion
			}
		}
		else
		{
			if (rotTile1 > 0.0f)
			{
				rotTile1 -= 10.0f * deltaTime; // Decrementa la rotación
			}
			else
			{
				n1 = false;
			}
		}
	}

	if (n1) // no permite cambios en el ciclo
		return;

	if (activAnim2 && n2) // si ambas estan encendidas
	{
		if (pokeballAbierta2)
		{
			if (rotTile2 < 45.0f)
			{
				rotTile2 += 10.0f * deltaTime; // Incrementa la rotación 
			}
			else
			{
				n2 = false; // fin de la aimacion
			}
		}
		else
		{
			if (rotTile2 > 0.0f)
			{
				rotTile2 -= 10.0f * deltaTime; // Decrementa la rotación
			}
			else
			{
				n2 = false;
			}
		}
	}

	if (n2) // no permite cambios en el ciclo
		return;


}



// Is called whenever a key is pressed/released via GLFW
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_Z && action == GLFW_PRESS)
	{
		rotatePoke2 = !rotatePoke2; // Cambia el estado de la rotación
	}

	if (key == GLFW_KEY_5 && action == GLFW_PRESS)
	{
		activePot - false; // Cambia el estado de la rotación
	}

	if (key == GLFW_KEY_8 && !rotatePintu) {
		rotatePintu = true;  // Activa la rotación de la pintura
	}

	if (keys[GLFW_KEY_1] && !moveSofa1Negative) {
		moveSofa1Negative = true;
	}

	if (keys[GLFW_KEY_2] && !moveSofa1Positive) {
		moveSofa1Positive = true;
	}

	if (GLFW_KEY_ESCAPE == key && GLFW_PRESS == action)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}



	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			keys[key] = true;
		}
		else if (action == GLFW_RELEASE)
		{
			keys[key] = false;
		}
	}
	

	if (keys[GLFW_KEY_SPACE] && !active)
	{
		activePot = !activePot;
		if (activePot)
		{
			LightP1 = glm::vec3(1.0f, 1.0f, 1.0f); //
		}
		else
		{
			LightP1 = glm::vec3(0);
		}
	}

	if (keys[GLFW_KEY_V] && !active)
	{
		activePot = !activePot;
		if (activePot)
		{
			LightP2 = glm::vec3(0.0f, 1.0f, 1.0f); //
		}
		else
		{
			LightP2 = glm::vec3(0);//Cuado es solo un valor en los 3 vectores pueden dejar solo una componente
		}
	}

	if (keys[GLFW_KEY_0])
	{
		activePot = !activePot;
		if (activePot)
		{
			LightP3 = glm::vec3(1.0f, 1.0f, 1.0f); //
		}
		else
		{
			LightP3 = glm::vec3(0);//Cuado es solo un valor en los 3 vectores pueden dejar solo una componente
		}
	}

	if (keys[GLFW_KEY_N])
	{
		activePot = !activePot;
		if (activePot)
		{
			LightP4 = glm::vec3(0.93f, 0.89f, 0.69f); //0.93f, 0.89f, 0.69f
		}
		else
		{
			LightP4 = glm::vec3(0);//Cuado es solo un valor en los 3 vectores pueden dejar solo una componente
		}

	}

	if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS)
	{
		if (!n1) // Se niega la modificacion mientras este animado
		{
			pokeballAbierta = !pokeballAbierta;
			n1 = true; // Inicia la animación 
		}
	}

	if (glfwGetKey(window, GLFW_KEY_7) == GLFW_PRESS)
	{
		if (!n2) // Se niega la modificacion mientras este animado
		{
			pokeballAbierta2 = !pokeballAbierta2;
			n2 = true; // Inicia la animación 
		}
	}

}


void MouseCallback(GLFWwindow* window, double xPos, double yPos)
{
	if (firstMouse)
	{
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}

	GLfloat xOffset = xPos - lastX;
	GLfloat yOffset = lastY - yPos;  // Reversed since y-coordinates go from bottom to left

	lastX = xPos;
	lastY = yPos;

	camera.ProcessMouseMovement(xOffset, yOffset);
}

void animacion() //circuito de la pokebola
{

	if (circuito)
	{
		if (recorrido1)
		{
			movKitY += 0.1f;
			movKitX += 0.1f;
			if (movKitY > 2)
			{
				recorrido1 = false;
				recorrido2 = true;
			}
		}
		else if (recorrido2)
		{
			movKitY -= 0.1f;
			if (movKitY < -1.45)
			{
				recorrido2 = false;
				recorrido3 = true;
			}
		}
		else if (recorrido3)
		{
			movKitY += 0.1f;
			movKitX += 0.1f;
			if (movKitY > 0.5)
			{
				recorrido3 = false;
				recorrido4 = true;
			}
		}

		if (recorrido4)
		{
			movKitY -= 0.1f;
			if (movKitY < -1.45)
			{
				recorrido4 = false;
				//recorrido1 = true;

			}
		}
	}
}

void animacion1() //circuito de mimikyu
{
	if (circuito1)
	{
		if (reco1)
		{
			rotPik = 360;
			movPikX += 0.1f;
			if (movPikX > 16.5) {
				reco1 = false;
				reco2 = true;
			}
		}

		else if (reco2)
		{
			rotPik = 90;
			movPikZ -= 0.1f;
			if (movPikZ < -9.0)
			{
				reco2 = false;
				reco3 = true;
			}
		}

		else if (reco3)
		{
			rotPik = 270;
			movPikY += 0.1f;
			if (movPikY > 1.75)
			{
				reco3 = false;
			}
		}
	}
}