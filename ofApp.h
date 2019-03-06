/************************************************************
■fix in ofSoundStream
URL
	https://forum.openframeworks.cc/t/ofsoundstream-different-sound-device-for-input-and-output/11087/9

purpose
	different audio devices for audio input and output.
	
fix files
	/Users/nobuhiro/Documents/source/openframeworks/of_v0.9.0_osx_release/libs/openFrameworks/sound/
	上記URLでは、"ofBaseSoundStream.cpp"となっているが、正しくは、"ofSoundStream.cpp".
		ofBaseSoundStream.h
		ofSoundStream.cpp
		ofSoundStream.h
	
fix point
	ofBaseSoundStream.h
		add 2 lines.
			virtual void setInDeviceID(int deviceID) = 0;  
			virtual void setOutDeviceID(int deviceID) = 0;  
	
	ofSoundStream.cpp
		add 2 functions.
			void ofSoundStream::setInDeviceID(int deviceID){  
				if( soundStream ){  
					soundStream->setInDeviceID(deviceID);  
				}  
			}  
			
			void ofSoundStream::setOutDeviceID(int deviceID){  
				if( soundStream ){  
					soundStream->setOutDeviceID(deviceID);  
				}  
			}  
	
	ofSoundStream.h
		add 2 lines.
			void setInDeviceID(int deviceID);  
			void setOutDeviceID(int deviceID);  
			
	
How to use
	soundStream.setInDeviceID(InDevID);
	soundStream.setOutDeviceID(OutDevID);

■Audio I/F
input:cable
	基本モノラル(多分)。
	LRはもちろん、Hot/Cold/GNDなどの表記があるか、注意して見ること。
	
	つまり、walkmanからinputする時は、LR(白赤)に分けて入れること。
	ちなみに、「標準ステレオ」をinputしたつもりで動作させると、
	「低音スカスカなんだけど」って感じになった。
	
input:Level
	walkmanから入れる場合、cable上のLevelはLine Level。
	なので、input感度は、minimumに設定すること。
	
	

■primitive study
	■DTM初心者のためのオーディオインターフェイス選び 2016
		http://www.dtmstation.com/archives/51971048.html
	
	■「ｄＢ（デシベル）その１～音圧レベル」～音響豆知識(２)
		http://blogs.yahoo.co.jp/boorankenko/43674244.html
	
	■「ｄＢ（デシベル）その２～ラインレベルのいろいろ」～音響豆知識（３）
		http://blogs.yahoo.co.jp/boorankenko/43695409.html	
			mic Level/ Line Level/ Speaker(or Amp) Level
		
	■「ｄＢ（デシベル）その３～マイクレベル」～音響豆知識（４）
		http://blogs.yahoo.co.jp/boorankenko/43753018.html
	
	
	■オーディオ信号レベル
		http://detail.chiebukuro.yahoo.co.jp/qa/question_detail/q1413957214
			マイク 1.6mV
			エレキギター 200mV
			ライン 1,230mV（1,000mV）
			ヘッドフォン、スピーカー 2,400-2.830mV

■【今さら聞けない用語シリーズ】
	■初心者向け【今さら聞けない用語シリーズ】初めてのオーディオ・インターフェース選び
		http://info.shimamura.co.jp/digital/knowledge/2014/06/21591
		
	■【今さら聞けない用語シリーズ】3分でわかる！インピーダンスって何でしょう？ ロー出しハイ受け？
		http://info.shimamura.co.jp/digital/knowledge/2014/01/16805
		
	■【今さら聞けない用語シリーズ】3分でわかる！オーディオ・ケーブルの種類とバランス・アンバランスの違い
		http://info.shimamura.co.jp/digital/knowledge/2014/01/16501
		
	■【今さら聞けない用語シリーズ】音と周波数
		http://info.shimamura.co.jp/digital/knowledge/2014/03/19260
		
	■【今さら聞けない用語シリーズ】3分でわかる！コンデンサーマイクとダイナミックマイクの違い おすすめマイク
		http://info.shimamura.co.jp/digital/knowledge/2014/04/23017

************************************************************/
#pragma once

/************************************************************
************************************************************/
#include "ofMain.h"

/************************************************************
************************************************************/
enum{
	AUDIO_BUF_SIZE = 512,
	AUDIO_BUFFERS = 2,
	AUDIO_SAMPLERATE = 44100,
};


/************************************************************
************************************************************/
class ofApp : public ofBaseApp{
private:
	/****************************************
	****************************************/
	enum{
		WIDTH	= 400,
		HEIGHT	= 400,
	};
	
	/****************************************
	****************************************/
	int soundStream_Input_DeviceId;
	int soundStream_Output_DeviceId;
	ofSoundStream soundStream;
	
	vector<float> samplesLeft;
	vector<float> samplesRight;
	
	/****************************************
	****************************************/
	void audioIn(float *input, int bufferSize, int nChannels);
	void audioOut(float *output, int bufferSize, int nChannels);
	
public:
	/****************************************
	****************************************/
	ofApp(int _soundStream_Input_DeviceId, int _soundStream_Output_DeviceId);
	
	void setup();
	void update();
	void draw();
	

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
	
};
