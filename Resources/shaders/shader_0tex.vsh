attribute vec4 a_position;//(����)���W
attribute vec4 a_color; //�F

//(����)���[���h�A�r���[�A�v���W�F�N�V�����s��
uniform mat4 u_wvp_matrix;

//(�o��)�F
varying vec4 v_color;

void main()
{
	//���͍��W�����[���h�A�r���[�A�v���W�F�N�V����(�ˉe)�ϊ�
	gl_Position = u_wvp_matrix * a_position;
	//���͂���o�͂ɐF���R�s�[
	v_volor = a_color;

	//�V�F�[�_�[�̏o�͂ɍ��W���R�s�[
	gl_Position = a_position;
}