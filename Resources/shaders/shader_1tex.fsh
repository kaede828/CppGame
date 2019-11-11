//(����)�F
varying vec4 v_color;
//(����)�e�N�X�`�����W
varying vec2 v_texCoord;
//(����)�e�N�X�`���T���v���[
uniform sampler2D sampler;

void main()
{
 //�e�N�X�`���̎w����W�̐F���擾
 vec4 texcolor = texture2D(sampler,v_texCoord);
 //�e�N�X�`���J���[�ƒ��_�J���[���|���ďo��
 gl_FragColor = texcolor * v_color;
 //gl_FragColor = vec4(1,1,1,1);
}