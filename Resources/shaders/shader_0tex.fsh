varying vec4 v_color;//(����)�F

void main()
{
 //�V�F�[�_�[�̏o�͂ɃJ���[���R�s�[
 gl_FragColor = v_color;
 //�V�F�[�_�[�o�͂�RGBA�ŃJ���[��ݒ�
 gl_FragColor = vec4(10.0,1.0,1.0,1.0);
}