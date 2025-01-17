/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
	return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object
	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

	if (closeItem == nullptr ||
		closeItem->getContentSize().width <= 0 ||
		closeItem->getContentSize().height <= 0)
	{
		problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
	}
	else
	{
		float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
		float y = origin.y + closeItem->getContentSize().height / 2;
		closeItem->setPosition(Vec2(x, y));
	}

	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	/////////////////////////////
	// 3. add your codes below...

	// add a label shows "Hello World"
	// create and initialize a label

	auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
	if (label == nullptr)
	{
		problemLoading("'fonts/Marker Felt.ttf'");
	}
	else
	{
		// position the label on the center of the screen
		label->setPosition(Vec2(origin.x + visibleSize.width / 2,
			origin.y + visibleSize.height - label->getContentSize().height));

		// add the label as a child to this layer
		this->addChild(label, 1);
	}

	// add "HelloWorld" splash screen"
	auto sprite = Sprite::create("HelloWorld.png");
	if (sprite == nullptr)
	{
		problemLoading("'HelloWorld.png'");
	}
	else
	{
		// position the sprite on the center of the screen
		sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

		// add the sprite as a child to this layer
		//this->addChild(sprite, 0);
	}

	//OpenGLのエラーコードを受ける変数
	GLenum error;

	m_pProgram = new GLProgram;
	//シェーダーをテキストファイルから読み込んでコンパイル
	m_pProgram->initWithFilenames("shaders/shader_0tex.vsh", "shaders/shader_0tex.fsh");
	error = glGetError();
	//attribute変数に属性インデックスを割り振る
	m_pProgram->bindAttribLocation("a_position", GLProgram::VERTEX_ATTRIB_POSITION);
	error = glGetError();
	//attribute変数に属性インデックスを割り振る
	m_pProgram->bindAttribLocation("a_color", GLProgram::VERTEX_ATTRIB_COLOR);
	error = glGetError();
	//attribute変数に属性インデックスを割り振る
	/*m_pProgram->bindAttribLocation("a_texCoord", GLProgram::VERTEX_ATTRIB_TEX_COORD);
	error = glGetError();*/
	//シェーダープログラムをリンク
	m_pProgram->link();
	//uniform変数のリストを保存
	m_pProgram->updateUniforms();
	error = glGetError();

	//uniform変数の番号を取得
	uniform_wvp_matrix = glGetUniformLocation(m_pProgram->getProgram(), "u_wvp_matrix");


	//uniform_sampler = glGetUniformLocation(m_pProgram->getProgram(), "sampler");
	//テクスチャ読み込み
	//m_pTexture = Director::getInstance()->getTextureCache()->addImage("pink.jpg");

	//Director::getInstance()->setClearColor(Color4F(0, 1, 0, 0));

	/*counter = 0;
	Step = false;*/

	return true;
}

void HelloWorld::draw(Renderer *renderer, const Mat4& transform, uint32_t flags)
{
	//glBlendFunc(GL_ONE, GL_ONE);

	GLenum error;
	//指定したフラグに対応する属性インデックスだけを有効にして、他は無効にする
	GL::enableVertexAttribs(GL::VERTEX_ATTRIB_FLAG_POSITION | GL::VERTEX_ATTRIB_FLAG_COLOR | GL::VERTEX_ATTRIB_FLAG_TEX_COORD);
	//シェーダーを有効化する
	m_pProgram->use();
	//error = glGetError();

	counter++;
	//三角形の３頂点分の座標
	Vec3 pos[6];
	Vec4 color[6];
	//Vec2 uv[6];
	const float x = 50.0f;
	const float y = 50.0f;
	for (int n = 0; n < 11; n++)
		//座標を１点ずつ設定
		pos[0] = Vec3(-x-counter/120.0f, -y+counter/120.f, 0);
	pos[1] = Vec3(-x - counter / 120.0f, y + counter / 120.f, 0);
	pos[2] = Vec3(x - counter / 120.0f, -y + counter / 120.f, 0);
	pos[3] = Vec3(-x + counter / 120.0f, y - counter / 120.f, 0);

	/*pos[4] = Vec3(x + counter / 120.0f, -y - counter / 120.f, 0);
	pos[5] = Vec3(x + counter / 120.0f, y - counter / 120.f, 0);*/

	//カラーを一点ずつ設定
	color[0] = Vec4(1, 1, 1, 1);//黒
	color[1] = Vec4(1, 1, 1, 1);//赤
	color[2] = Vec4(1, 1, 1, 1);//緑
	color[3] = Vec4(1, 1, 1, 1);//青
	/*color[4] = Vec4(1, 1, 1, 1);
	color[5] = Vec4(1, 1, 1, 1);*/

	//テクスチャ座標を1点ずつ設定
	uv[0] = Vec2(0, 1);
	uv[1] = Vec2(0, 0);
	uv[2] = Vec2(1, 1);
	uv[3] = Vec2(0, 0);
	uv[4] = Vec2(1, 1);
	uv[5] = Vec2(1, 0);

	//counter++;

	float red = 1;
	float green = 0;
	float blue = 0;



	/*if (Step)
	{
		red = 0.0f;
		green = 1.0f - counter / 60.0f;
		blue = 0.0f + counter / 60.0f;
	}
	else
	{
		red = 1.0f - counter / 60.0f;
		green = 0.0f + counter / 60.0f - counter / 120.0f;
		blue = 0.0f;
			if (counter >= 60)
			{
				Step = true;
				counter = 0;
			}
	}*/


	////カラー変更
	//Vec4 color[4];
	//color[0] = Vec4(red, green, blue,0.1f);//黒
	//color[1] = Vec4(red, green, blue,0.1f);//赤
	//color[2] = Vec4(red, green, blue,0.1f);//緑
	//color[3] = Vec4(red, green, blue,0.1f);//青



	//指定した属性インデックスに、データを関連付ける
	glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 3, GL_FLOAT, GL_FALSE, 0, pos);

	glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_FLOAT, GL_FALSE, 0, color);

	//指定した属性インデックスに、データを関連付ける
	glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_TEX_COORD, 2, GL_FLOAT, GL_FALSE, 0, uv);

	//スケーリング行列
	Mat4 matWorld = Mat4::IDENTITY;
	Mat4 matScale;
	//全方向２倍のスケーリング行列を生成
	Mat4::createScale(2.0f, 2.0f, 2.0f, &matScale);

	Mat4 matRot;
	Mat4 matRotX, matRotY, matRotZ;
	//回転 Z軸周りlラジアン→X軸周りmラジアン→Y軸周りnラジアンの順に
	Mat4::createRotationZ(3.14f, &matRotZ);
	Mat4::createRotationX(3.14f, &matRotZ);
	Mat4::createRotationY(3.14f, &matRotZ);
	matRot = matRotY * matRotX * matRotZ;

	Mat4 matTrans;
	Mat4::createTranslation(Vec3(1.0f, 1.0f, 1.0f), &matTrans);

	matWorld = matTrans * matRot * matScale;


	//指定したuniform変数にテクスチャを関連付ける
	glUniform1i(uniform_sampler, 0);
	GL::bindTexture2D(m_pTexture->getName());

	//4頂点分のデータで三角形を描画する
	//glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);


	////2つ目の四角形の座標と色を指定
	//pos[0].x += 0.1f; pos[0].y += 0.1f;
	//pos[1].x += 0.1f; pos[1].y += 0.1f;
	//pos[2].x += 0.1f; pos[2].y += 0.1f;
	//pos[3].x += 0.1f; pos[3].y += 0.1f;

	//color[0] = Vec4(0, 0, 1,0.5f);
	//color[1] = Vec4(0, 0, 1,0.5f);
	//color[2] = Vec4(0, 0, 1,0.5f);
	//color[3] = Vec4(0, 0, 1,0.5f);

	glDrawArrays(GL_TRIANGLES, 0, 6);

	//glDrawArrays(GL_TRIANGLES, 1, 3);
	error = glGetError();
}
void HelloWorld::menuCloseCallback(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();

	/*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

	//EventCustom customEndEvent("game_scene_close_event");
	//_eventDispatcher->dispatchEvent(&customEndEvent);


}
