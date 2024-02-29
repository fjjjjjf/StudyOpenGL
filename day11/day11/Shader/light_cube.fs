#version 330 core

out vec4 FragColor;
in vec3 Normal;
in vec3 FragPos;

uniform vec3 lightPos; 
uniform vec3 lightColor;
uniform vec3 objectColor;

uniform vec3 viewPos;//��������λ��


struct Material{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};
uniform Material material;

struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Light light;

void main()
{
        // ������
     
        vec3 ambient = material.ambient * light.ambient;
       
        //diffuse
        vec3 norm = normalize(Normal);
        vec3 lightDir = normalize(lightPos - FragPos);//�����Դ��Ƭ��λ��֮��ķ�������
    
        float diff = max(dot(norm, lightDir), 0.0);//��norm��lightDir�������е�ˣ������Դ�Ե�ǰƬ��ʵ�ʵ�������Ӱ�졣���ֵ�ٳ��Թ����ɫ���õ������������
        vec3 diffuse = diff * light.diffuse* material.diffuse;//�����������֮��ĽǶȴ���90�ȣ���˵Ľ���ͻ��ɸ����������ᵼ�������������Ϊ������Ϊ�ˣ�����ʹ��max����������������֮��ϴ�Ĳ������Ӷ���֤��������������ɸ�����
         
        //�߹�
      
        vec3 viewDir =normalize(viewPos-FragPos);
        vec3 reflectDir =reflect(-lightDir,norm);//ȡ��lightdir��ָ���Ǵ�Ƭ��ָ���Դ����������֤�����ȷreflect

        float spec =pow(max(dot(viewDir,reflectDir),0.0f),material.shininess);
        vec3 specular =material.specular*spec*light.specular;

        vec3 result = (ambient + diffuse+ specular) * objectColor;
        FragColor = vec4(result,1.0); 
   }