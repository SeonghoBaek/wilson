/**
*
*  @author		Seongho Baek
*  @date		2014.08.12
*/

#include "Normalizer.h"
#include "Types.h"
#include "List.h"
#include "Log.h"
#include "Lock.h"

#include <ctype.h>
#include <string.h>
#include <math.h>

SessionMeanVectorList::SessionMeanVectorList()
{
	this->mLock = Lock::createMutex();
	this->mpSMVL = new MeanVector();
}

float SessionMeanVectorList::getMean(int dim, unsigned int session)
{
	float mean = 0;
	MeanVector *pMV = NULL;

	LOCK(this->mLock)
	{
		LIST_FOR_EACH(pMV, this->mpSMVL)
		{
			if (pMV->getSession() == session)
			{
				mean = pMV->getMean(dim);

				break;
			}
		}
	}

	return mean;
}

float SessionMeanVectorList::calMean(int dim, float length, unsigned int session)
{
	float mean = 0;
	MeanVector *pMV = NULL;

	LOCK(this->mLock)
	{
		LIST_FOR_EACH(pMV, this->mpSMVL)
		{
			if (pMV->getSession() == session)
			{
				mean = pMV->calMean(dim, length);

				break;
			}
		}
	}

	return mean;
}

void SessionMeanVectorList::incSessionSize(unsigned int session)
{
	LOCK(this->mLock)
	{
		MeanVector *pVector;

		LIST_FOR_EACH(pVector, this->mpSMVL)
		{
			if (pVector->getSession() == session)
			{
				pVector->incSessionSize();

				break;
			}
		}

		// Create new MeanVector
		if (pVector == this->mpSMVL)
		{
			pVector = new MeanVector(session);
			pVector->incSessionSize();

			LIST_ADD(pVector, this->mpSMVL);
		}
	}
}

void SessionMeanVectorList::decSessionSize(unsigned int session)
{
	LOCK(this->mLock)
	{
		MeanVector *pVector;

		LIST_FOR_EACH(pVector, this->mpSMVL)
		{
			if (pVector->getSession() == session)
			{
				pVector->decSessionSize();

				if (pVector->getSessionSize() == 0)
				{
					LIST_DEL(pVector);

					delete pVector;
				}

				break;
			}
		}
	}
}

SessionMeanVectorList::~SessionMeanVectorList()
{
	if (this->mLock) Lock::deleteMutex(this->mLock);

	MeanVector *pVector;

	LIST_FOR_EACH(pVector, this->mpSMVL)
	{
		MeanVector *pDel = pVector;
		LIST_DEL(pDel);
		delete pDel;
		pVector = this->mpSMVL;
	}

	delete this->mpSMVL;
}

MeanVector::MeanVector()
{
	// Dummy.
	LIST_INIT(this);
}

MeanVector::MeanVector(unsigned int session)
{
	this->mpLengthArray = new float[MAX_VECTOR_LENGTH];
	memset(this->mpLengthArray, 0, sizeof(float)*MAX_VECTOR_LENGTH);
	this->mpSizeArray = new int[MAX_VECTOR_LENGTH];
	memset(this->mpSizeArray, 0, sizeof(float)*MAX_VECTOR_LENGTH);
	this->mDimension = MAX_VECTOR_LENGTH;
	this->mLock = Lock::createMutex();
	this->mSession = session;
	this->mSessionSize = 0;

	LIST_INIT(this);
}

MeanVector::~MeanVector()
{
	LIST_DEL(this);
	if (this->mpLengthArray) delete [] this->mpLengthArray;
	if (this->mpSizeArray) delete [] this->mpSizeArray;
	if(this->mLock) Lock::deleteMutex(this->mLock);
}

unsigned int MeanVector::getSessionSize()
{
	unsigned int size = 0;

	LOCK(this->mLock)
	{
		size = this->mSessionSize;
	}

	return size;
}

void MeanVector::incSessionSize()
{
	LOCK(this->mLock)
	{
		this->mSessionSize++;
	}
}

void MeanVector::decSessionSize()
{
	LOCK(this->mLock)
	{
		this->mSessionSize--;
	}
}

float MeanVector::calMean(int dim, float length)
{
	LOCK(this->mLock)
	{
		if (dim >= this->mDimension)
		{
			float *pNewLengthArray = new float[this->mDimension + MAX_VECTOR_LENGTH];
			memset(pNewLengthArray, 0, sizeof(float)*(this->mDimension + MAX_VECTOR_LENGTH));
			memcpy(pNewLengthArray, this->mpLengthArray, sizeof(float)*(this->mDimension));
			delete [] this->mpLengthArray;
			this->mpLengthArray = pNewLengthArray;

			int *pNewSizeArray = new int[this->mDimension + MAX_VECTOR_LENGTH];
			memset(pNewSizeArray, 0, sizeof(int)*(this->mDimension + MAX_VECTOR_LENGTH));
			memcpy(pNewSizeArray, this->mpSizeArray, sizeof(int)*(this->mDimension));
			delete [] this->mpSizeArray;
			this->mpSizeArray = pNewSizeArray;

			this->mDimension += MAX_VECTOR_LENGTH;
		}

		this->mpLengthArray[dim] = this->mpLengthArray[dim]*this->mpSizeArray[dim] + length;
		this->mpSizeArray[dim]++;
		this->mpLengthArray[dim] /= this->mpSizeArray[dim];

		//LOGI("Mean Vector Length[%d]:%f", dim, this->mpLengthArray[dim]);
	}

	return this->mpLengthArray[dim];
}

float MeanVector::getMean(int dim)
{
	float mean = 0;

	LOCK(this->mLock)
	{
		mean = this->mpLengthArray[dim];
	}

	return mean;
}

char *Term::toJSON()
{
	char* terms = new char[MAX_TERM_LENGTH+1];

	memset(terms,0,MAX_TERM_LENGTH+1);

	sprintf(terms, "{\"term\":\"%s\",\"freq\":%d}", this->value, this->freq);

	return terms;
}

int TermVector::addTerm(Term* pTerm)
{
	LIST_ADD(pTerm, this->mpTermList);

	this->mNumOfTerms++;

	return this->mNumOfTerms;
}

char* TermVector::toJSON(char *log)
{
	char *vector = new char[MAX_VECTOR_LOG_LENGTH+1];

	memset(vector, 0, MAX_VECTOR_LOG_LENGTH+1);

	sprintf(vector, "\"vectors\":[{\"distance\":%d,\"version\":%d,\"offset\":%lld,\"text\":\"%s\",\"terms\":",
			this->mDistance, this->mVersion, this->mOffset,log);


	strcat(vector,"[");

	Term* pTerm = NULL;
	bool bStart = TRUE;

	LIST_FOR_EACH(pTerm, this->mpTermList)
	{
		char* termJson = pTerm->toJSON();

		if (!bStart) strcat(vector, ",");
		bStart = FALSE;

		strcat(vector, termJson);

		delete [] termJson;
	}

	strcat(vector,"]}]");

	return vector;
}

char* TermVector::toJSON()
{
	char *vector = new char[MAX_VECTOR_LENGTH+1];

	memset(vector, 0, MAX_VECTOR_LENGTH+1);

	sprintf(vector, "\"vector\":[{\"distance\":%d,\"version\":%d,\"offset\":%lld, \"terms\":",
			this->mDistance, this->mVersion, this->mOffset);

	strcat(vector,"[");

	Term* pTerm = NULL;
	bool bStart = TRUE;

	LIST_FOR_EACH(pTerm, this->mpTermList)
	{
		char* termJson = pTerm->toJSON();

		if (!bStart) strcat(vector, ",");
		bStart = FALSE;

		strcat(vector, termJson);

		delete [] termJson;
	}

	strcat(vector,"]}]");

	return vector;
}

TermVector::~TermVector()
{
	Term *pTerm = NULL;

	LIST_FOR_EACH(pTerm, this->mpTermList)
	{
		LIST_DEL(pTerm);

		delete pTerm;

		pTerm = this->mpTermList;
	}

	delete pTerm;
}

int TermVector::getDistance(TermVector *tv)
{
	Term *pTerm1 = NULL;
	Term *pTerm2 = NULL;
	float power = 0;
	float length = 0;

	pTerm2 = this->mpTermList->p_next;

	LIST_FOR_EACH(pTerm1, tv->getTermList())
	{
		power += (pTerm1->pri * pow(pTerm1->freq - pTerm2->freq, 2));
		pTerm2 = pTerm2->p_next;
	}

	float dist = sqrt(power);

	//LOGI("Distance: %f\n", dist);

	return (int)dist;
}

TermVector* Normalizer::transform(char *data, int size, char** terms, int nrTerms)
{
	_GOODNESS(data, NULL);
	_GOODNESS(terms, NULL);

	if (nrTerms == 0) return NULL;

	TermVector *tv = new TermVector;

	// Make terms.
	for (int i = 0; i < nrTerms; i++)
	{
		if (terms[i] == NULL)
		{
			delete tv;

			return NULL;
		}

		Term *term = new Term();

		term->pri = nrTerms - i;
		strncpy(term->value, terms[i], MAX_TERM_LENGTH);

		tv->addTerm(term);
	}

	// Term Match.
	match(data, size, tv);

	// Normalize Vector.
	Term* pTerm = NULL;
	float length = 0;

	LIST_FOR_EACH(pTerm, tv->getTermList())
	{
		//LOGI("Term %s: %d", pTerm->value, pTerm->freq);

		length += (pTerm->freq * pTerm->freq);
	}

	length = sqrt(length);

	//LOGI("Vector Length: %f", length);
	tv->setLength(length);

	/*
	if (length)
	{
		LIST_FOR_EACH(pTerm, tv->getTermList())
		{
			pTerm->freq = (int)(pTerm->freq / length);
		}
	}
	*/

	return tv;
}

int Normalizer::match(char *data, int size, TermVector *tv)
{
	Term *pTerm = NULL;

	normalizeCharacter(data, size, NULL);

	LIST_FOR_EACH(pTerm, tv->getTermList())
	{
		int len = (int)strlen(pTerm->value);

		for (int i = 0; i <= size - len; i++)
		{
			if ( strncmp(pTerm->value, data+i, len) == 0 )// Match
			{
				pTerm->freq++;
				i += len;
			}
		}
	}

	return 0;
}

char *Normalizer::normalizeCharacter(char *str, int length, char *target)
{
    for (int i = 0; i < length; i++)
    {
    	str[i] = toupper(str[i]);

    	if (str[i] == '\"' || str[i] == '$' || str[i] == '\t')
    	{
    		str[i] = ' ';
    		continue;
    	}

    	if (str[i] == 0x1B)
    	{
    		str[i++] = ' ';
    		str[i] = ' ';
    		continue;
    	}
    }

    return target;
}

