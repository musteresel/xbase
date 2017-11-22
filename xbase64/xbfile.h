#ifndef __XB_FILE_H__
#define __XB_FILE_H__

#ifdef __GNU_LesserG__
#pragma interface
#endif

class XBDLLEXPORT xbFile {
public:
	xbFile() {}
	virtual const char * GetExtWithDot(bool lower) = 0;
	const xbString & GetFileName() { return fileName_; }
	xbString MakeFileName(const char * filename);

protected:
	void SetFileName(const char * filename) {
		fileName_ = MakeFileName(filename);
	}

private:
	xbString fileName_;
};

#endif  // XBFILE_H
