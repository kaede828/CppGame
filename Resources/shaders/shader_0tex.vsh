attribute vec4 a_position;//(入力)座標
attribute vec4 a_color; //色

//(入力)ワールド、ビュー、プロジェクション行列
uniform mat4 u_wvp_matrix;

//(出力)色
varying vec4 v_color;

void main()
{
	//入力座標をワールド、ビュー、プロジェクション(射影)変換
	gl_Position = u_wvp_matrix * a_position;
	//入力から出力に色をコピー
	v_volor = a_color;

	//シェーダーの出力に座標をコピー
	gl_Position = a_position;
}