#version 330 core

out vec4 FragColor;
in vec3 Normal;
in vec3 FragPos;

uniform vec3 lightPos; 
uniform vec3 lightColor;
uniform vec3 objectColor;

uniform vec3 viewPos;//��������λ��
uniform int Value;

void main()
{
        // ������
        float ambientStrength = 0.1;
        vec3 ambient = ambientStrength * lightColor;
       
        //diffuse
        vec3 norm = normalize(Normal);
        vec3 lightDir = normalize(lightPos - FragPos);//�����Դ��Ƭ��λ��֮��ķ�������
    
        float diff = max(dot(norm, lightDir), 0.0);//��norm��lightDir�������е�ˣ������Դ�Ե�ǰƬ��ʵ�ʵ�������Ӱ�졣���ֵ�ٳ��Թ����ɫ���õ������������
        vec3 diffuse = diff * lightColor;//�����������֮��ĽǶȴ���90�ȣ���˵Ľ���ͻ��ɸ����������ᵼ�������������Ϊ������Ϊ�ˣ�����ʹ��max����������������֮��ϴ�Ĳ������Ӷ���֤��������������ɸ�����
         
        //�߹�
        float specularStrengh = 0.5;
        vec3 viewDir =normalize(viewPos-FragPos);
        vec3 reflectDir =reflect(-lightDir,norm);//ȡ��lightdir��ָ���Ǵ�Ƭ��ָ���Դ����������֤�����ȷreflect

        float spec =pow(max(dot(viewDir,reflectDir),0.0f),Value);
        vec3 specular =specularStrengh*spec*lightColor;

        vec3 result = (ambient + diffuse+ specular) * objectColor;
        FragColor = vec4(result,1.0); 
   }