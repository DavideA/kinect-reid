#pragma once

#include "Model.h"
#include "Acquisition.h"
#include <map>
#include <vector>

typedef std::map<char, Model>::iterator ModelIterator;
typedef std::map<char, Model> ModelMap;

class ModelExtractor{



public:
	ModelExtractor();
	~ModelExtractor();

	ModelMap				EvalModels(Frame currFrame, unsigned char nBins);
private:


	ModelMap				models;
	Frame					m_currFrame;
	OpenCVHelper			CVHelper;


};