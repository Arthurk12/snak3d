#version 330 core

// Atributos de fragmentos recebidos como entrada ("in") pelo Fragment Shader.
// Neste exemplo, este atributo foi gerado pelo rasterizador como a
// interpolação da posição global e a normal de cada vértice, definidas em
// "shader_vertex.glsl" e "main.cpp".
in vec4 position_world;
in vec4 normal;

// Posição do vértice atual no sistema de coordenadas local do modelo.
in vec4 position_model;

// Coordenadas de textura obtidas do arquivo OBJ (se existirem!)
in vec2 texcoords;

// Matrizes computadas no código C++ e enviadas para a GPU
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

// Identificador que define qual objeto está sendo desenhado no momento
#define PLANE  0
#define FRUIT  1
#define SNAKE_HEAD 2
#define BOTTOM_SIDE 3
#define LEFT_SIDE   4
#define TOP_SIDE    5
#define RIGHT_SIDE  6
#define LANDSCAPE 7
uniform int object_id;

// Parâmetros da axis-aligned bounding box (AABB) do modelo
uniform vec4 bbox_min;
uniform vec4 bbox_max;

// Variáveis para acesso das imagens de textura
uniform sampler2D TextureImage0;
uniform sampler2D TextureImage1;
uniform sampler2D TextureImage2;
uniform sampler2D TextureImage3;
uniform sampler2D TextureImage4;

// O valor de saída ("out") de um Fragment Shader é a cor final do fragmento.
out vec3 color;

// Constantes
#define M_PI   3.14159265358979323846
#define M_PI_2 1.57079632679489661923

void main()
{
    // Obtemos a posição da câmera utilizando a inversa da matriz que define o
    // sistema de coordenadas da câmera.
    vec4 origin = vec4(0.0, 0.0, 0.0, 1.0);
    vec4 camera_position = inverse(view) * origin;

    // O fragmento atual é coberto por um ponto que percente à superfície de um
    // dos objetos virtuais da cena. Este ponto, p, possui uma posição no
    // sistema de coordenadas global (World coordinates). Esta posição é obtida
    // através da interpolação, feita pelo rasterizador, da posição de cada
    // vértice.
    vec4 p = position_world;

    // Normal do fragmento atual, interpolada pelo rasterizador a partir das
    // normais de cada vértice.
    vec4 n = normalize(normal);

    vec4 light_position = vec4(0.0,2.0,0.0,1.0);
    vec4 light_direction = normalize(vec4(0.0,-1.0,0.0,0.0));

    // Vetor que define o sentido da fonte de luz em relação ao ponto atual.
    vec4 l = normalize(light_position-p);

    // Vetor que define o sentido da câmera em relação ao ponto atual.
    vec4 v = normalize(l - p);

    // Vetor que define o sentido da reflexão especular ideal.
    vec4 r = -l+2*n*(dot(n,l));

    // Coordenadas de textura U e V
    float U = 0.0;
    float V = 0.0;

    // Obtemos a refletância difusa a partir da leitura da imagem
    vec3 textureColor;

    vec3 Ks = vec3(0.0,0.0,0.0); // Refletância especular
    vec3 Ka = vec3(0.2,0.2,0.2); // Refletância ambiente
    float q = 10.0; // Expoente especular para o modelo de iluminação de Phong

    if ( object_id == FRUIT )
    {
        vec4 bbox_center = (bbox_min + bbox_max) / 2.0;

        vec4 p_texture = bbox_center + normalize(position_model-bbox_center);
        vec4 p_vector = p_texture - bbox_center;

        float theta = atan(p_vector.x, p_vector.z);
        float phi = asin(p_vector.y);

        U = (theta + M_PI  ) / (2*M_PI);
        V = (phi   + M_PI/2) / M_PI;
        textureColor = texture(TextureImage1, vec2(U,V)).rgb;
    }
    else if (object_id == SNAKE_HEAD) {
        float minx = bbox_min.x;
        float maxx = bbox_max.x;

        float miny = bbox_min.y;
        float maxy = bbox_max.y;

        float minz = bbox_min.z;
        float maxz = bbox_max.z;

        float texture_x = (position_model.x - minx) / (maxx-minx);
        float texture_y = (position_model.y - miny) / (maxy-miny);
        U = texture_x;
        V = texture_y;
        textureColor = texture(TextureImage2, vec2(U,V)).rgb;
    }
    else if ( object_id == LANDSCAPE )
    {
        vec4 bbox_center = (bbox_min + bbox_max) / 2.0;

        vec4 p_texture = bbox_center + normalize(position_model-bbox_center);
        vec4 p_vector = p_texture - bbox_center;

        float theta = atan(p_vector.x, p_vector.z);
        float phi = asin(p_vector.y);

        U = (theta + M_PI  ) / (2*M_PI);
        V = (phi   + M_PI/2) / M_PI;
        textureColor = texture(TextureImage3, vec2(U,V)).rgb;
    }
    else if( object_id == BOTTOM_SIDE   ||
             object_id == LEFT_SIDE     ||
             object_id == TOP_SIDE      ||
             object_id == RIGHT_SIDE)
     {
        U = texcoords.y;
        V = texcoords.x;
        textureColor = texture(TextureImage4, vec2(U,V)).rgb;;
     }
    else if ( object_id == PLANE )
    {
        // Coordenadas de textura do plano, obtidas do arquivo OBJ.
        U = texcoords.x;
        V = texcoords.y;
        textureColor = texture(TextureImage0, vec2(U,V)).rgb;;
    }

    vec3 I = vec3(1.0,1.0,1.0);

    vec3 Ia = vec3(0.2,0.2,0.2);

    // Equação de Iluminação
    float lambert = max(0,dot(n,l));

    vec3 lambert_diffuse_term = textureColor*I*max(0, dot(n,l));

    vec3 ambient_term = Ka*Ia;

    vec3 phong_specular_term  = Ks*I*pow(max(0,dot(r,v)), q);

    color = lambert_diffuse_term + ambient_term + phong_specular_term;

    // Cor final com correção gamma, considerando monitor sRGB.
    color = pow(color, vec3(1.0,1.0,1.0)/2.2);
}

