attribute vec4 a_position;//(����)���W

attribute vec4 a_color; //(����)�F
attribute vec2 a_texCoord; //(����)�e�N�X�`�����W

//(�o��)�F
varying vec4 v_color;
//(�o��)�e�N�X�`�����W
varying vec2 v_texCoord;

void main()
{
	//�V�F�[�_�[�̏o�͂ɍ��W���R�s�[
	gl_Position = a_position;
	//���͂���o�͂ɐF���R�s�[
	v_color = a_color;
	v_texCoord = a_texCoord;
}