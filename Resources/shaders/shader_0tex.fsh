varying vec4 v_color;//(入力)色

void main()
{
 //シェーダーの出力にカラーをコピー
 gl_FragColor = v_color;
 //シェーダー出力にRGBAでカラーを設定
 gl_FragColor = vec4(10.0,1.0,1.0,1.0);
}