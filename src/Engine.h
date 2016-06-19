#pragma once
#include "MainWindow.h"
#include "KinectAcquisition.h"
#include "FileAcquisition.h"
#include "ModelExtractor.h"
#include <map>

#define DISTANCE_MEASURES_COUNT 7

enum Method{
	L1,
	L2,
	Linf,
	BHATTACHARYYA,
	CORRELATION,
	INTERSECTION,
	CHISQ
};

struct Settings{
	Method histoDifference;

	Method jointNormalization;
	Method histoNormalization;

	int jointMask[NUI_SKELETON_POSITION_COUNT];
	float thresholds[DISTANCE_MEASURES_COUNT];

	unsigned char nBins;

	acquisition_type acqType;
	string dataFolder;

	bool recordMode;
	string saveFolder;
};

struct idxVal{
	unsigned	id;
	double		val;

	bool operator<(idxVal c){
		return (val < c.val);
	}
};

class Player{
public:
	
	Player(){}

	unsigned			skeleton_index;
	unsigned			enterFrame;
	unsigned			frameCounter;
	string				label;
	cv::Point2d			labelPosition;
	bool				checked; // if the trigger triggered for him
	vector<Model>		models;
};

typedef std::map<int, Player> PlayerDatabase;
typedef std::map<int, Player>::iterator PlayerDatabaseIterator;

class Engine {
	
public:
	Engine(HINSTANCE hInstance, int nCmdShow);
	~Engine();

	static Settings				settings;


public:
	static void CALLBACK		Update(Frame& f, std::string& status, PlayerDatabase& pdb, bool& updateTable);

	//Interface listeners:
	void						SetDistance(Method m);
	void						SetJointNormalization(Method m);
	void						SetHistoNormalization(Method m);

	void						ButtonClicked(bool right);

	void						JointsChanged(int jointId, bool checked);
	Settings					getSettings();

	void						updatePlayerLabel(int id, const std::string& label);

	static void					Uninitialize();

private:
	static acquisition_type		m_acqType;
	
	static vector<Player>		playersOnScene;
	static unsigned				frameCounter;
	static Ptr<Acquisition>		acquisition;

	static 	void				SaveFrame(Frame& currFrame);
	static unsigned				nSkeletons;

	static void					UpdatePlayersAndTrigger(Frame currFrame);
	static void					RemovePlayers();

	static PlayerDatabase		playersDatabase;

	static int					lastId;
	static int					guessedId;
	static Player				lastPlayer;

	static void					CompareAll(Player& p);
	static double				CompareModels(Model m1, Model m2);

	static string				_status;
	
	static bool					lastPlayerIdentificated;

	static unsigned				tp;
	static unsigned				fp;
	static unsigned				tn;
	static unsigned				fn;
	void						WritePerfOnFile(const string& filename);



	static Ptr<ModelExtractor>	extractor;

	void						InitSettings();
	static void					PlotLabels(Frame& currFrame);

	static void					UpdateStatusBar(const std::string& msg);

	static bool					_updateTable;


};