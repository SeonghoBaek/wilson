/*
 * Normalizer.h
 *
 *  Created on: Sep 16, 2014
 *      Author: major
 */

#ifndef NORMALIZER_H_
#define NORMALIZER_H_

#include "Types.h"
#include "List.h"
#include "Lock.h"

#define MAX_TERM_LENGTH 	80
#define MAX_VECTOR_LENGTH 	1024
#define MAX_VECTOR_LOG_LENGTH 16*1024
#define TOP_MAINTAIN_SIZE	10
#define MATCH_WINDOW_SIZE 	80

class MeanVector
{
	LINKED_LIST(MeanVector);

	private:
		float* mpLengthArray;
		int		mDimension;
		int* 	mpSizeArray;
		Mutex_t mLock;
		unsigned int mSession;
		unsigned int mSessionSize;

	public:
		MeanVector();
		MeanVector(unsigned int session);
		virtual ~MeanVector();

		float	calMean(int dim, float length);
		float	getMean(int dim);

		unsigned int getSession() {return mSession;}
		void	setSession(unsigned int session) {this->mSession = session;}
		void	incSessionSize();
		void 	decSessionSize();
		unsigned int getSessionSize();
};

class SessionMeanVectorList
{
	private:
		MeanVector *mpSMVL;
		Mutex_t mLock;

	public:
		SessionMeanVectorList();
		virtual ~SessionMeanVectorList();

		float	calMean(int dim, float length, unsigned int session);
		float	getMean(int dim, unsigned int session);
		void 	incSessionSize(unsigned int session);
		void	decSessionSize(unsigned int session);
};

class Term
{
	LINKED_LIST(Term);

	public:

		char value[MAX_TERM_LENGTH + 1];
		int freq;
		int pri;

		Term()
		{
			LIST_INIT(this);
			freq = 0;
			pri = 1;
			memset(value, 0, MAX_TERM_LENGTH + 1);
		}

		char* toJSON();

		virtual ~Term() {}
};

class TermVector
{
	LINKED_LIST(TermVector);

	private:

		Term *mpTermList;
		int mNumOfTerms;
		int mDistance;
		f_offset_t mOffset;
		int mVersion;
		int mLogSession;
		bool mGarbage;
		float mLength;

	public:

		TermVector()
		{
			mpTermList = new Term();
			mNumOfTerms = 0;
			mDistance = 0;
			mOffset = 0;
			mVersion = 0;
			mGarbage = FALSE;
			mLength = 0.0;
			mLogSession = 0;

			LIST_INIT(this);
		}

		virtual ~TermVector();

		char* toJSON();
		char* toJSON(char* log);

		int addTerm(Term* term);
		int getNumOfTerms() {return this->mNumOfTerms;}
		int getDistance() {return this->mDistance;}
		int getDistance(TermVector *tv);
		void setDistance(int distance) {this->mDistance = distance;}
		f_offset_t getOffset() {return this->mOffset;}
		void setOffset(f_offset_t offset) {this->mOffset = offset;}
		int getVersion() { return this->mVersion; }
		void setVersion(int version) { this->mVersion = version; }
		void setLogSession(int session) {this->mLogSession = session;}
		int getLogSession() {return this->mLogSession;}
		Term* getTermList() {return this->mpTermList;}
		bool isGarbage() { return this->mGarbage; }
		void setGarbage(bool bGarbage) { this->mGarbage = bGarbage; }
		float getLength() {return mLength;}
		void setLength(float length) {this->mLength = length;}
};

class Normalizer
{
	private:

		Normalizer() {}

		static int match(char *data, int size, TermVector *tv);
		static char *normalizeCharacter(char *str, int length, char* target);
	public:

		virtual ~Normalizer() {}

		static TermVector* transform(char *data, int size, char** terms, int nrTerms);
};

#endif /* NORMALIZER_H_ */
