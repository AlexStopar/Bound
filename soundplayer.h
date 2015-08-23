#ifndef SOUNDPLAYER_H
#define SOUNDPLAYER_H

class SoundPlayer
{
public:
	static SoundPlayer& getInstance()
	{
		static SoundPlayer instance; 
		return instance;
	}
	bool loadSounds();
	void playMusic();
	void pauseMusic();
	void stopMusic();
	void playWallHit();
	void playEnemyWallHit();
	void playLoseLife();
	void playDie();
	void playWarp();
	void playTitleDrop();
	void playMenuPick();
	void playMenuSwitch();
	void playHighScore();
	void playPause();
	void playCollect(bool isLifeGained);
	void free();
private:
	SoundPlayer() {};                  
	SoundPlayer(SoundPlayer const&);             
	void operator=(SoundPlayer const&);
	const int EASY_VOLUME = 60;
	const int SOUND_EFFECT_VOLUME = 20;
};

#endif