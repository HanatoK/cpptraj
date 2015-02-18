#ifndef INC_DATAFILELIST_H
#define INC_DATAFILELIST_H
#include "DataFile.h"
#include "DataSet.h"
#include "ArgList.h"
// Class: DataFileList
/// Holds a list of DataFile classes.
/** The DataFileList is meant to hold all output data files defined by any
  * Actions or Analysis. This allows multiple sets to be directed to the
  * same file etc. Holds both DataFiles, which hold DataSets, and CpptrajFiles
  * which are intended for plain ASCII text output (like from 'hbond avgout').
  */ 
class DataFileList {
  public:
    DataFileList();
    ~DataFileList();
    void Clear();
    DataFile* RemoveDataFile(DataFile*);
    void RemoveDataSet(DataSet*);
    void SetDebug(int);
#   ifdef MPI
    void SetEnsembleMode(int mIn) { ensembleMode_ = mIn; }
#   endif
    /// \return DataFile whose full path matches given string or 0.
    DataFile* GetDataFile(std::string const&) const;
    /// \return CpptrajFile whose full path matches given string or 0.
    CpptrajFile* GetCpptrajFile(std::string const&) const;
    /// Add DataFile to list if name specified, or return already existing DataFile.
    DataFile* AddDataFile(std::string const&, ArgList&);
    /// Add DataFile to list if name specified, or return already existing DataFile.
    DataFile* AddDataFile(std::string const&);
    // TODO: Deprecate in favor of AddDataFile
    DataFile* AddSetToFile(std::string const&,  DataSet*);
    /// Types of cpptrajfile that can be created.
    enum CFtype { TEXT = 0, PDB };
    /// Add CpptrajFile to list if name specified, or return already existing CpptrajFile.
    CpptrajFile* AddCpptrajFile(std::string const&,std::string const&);
    CpptrajFile* AddCpptrajFile(std::string const&,std::string const&,CFtype);
    CpptrajFile* AddCpptrajFile(std::string const&,std::string const&,CFtype,bool);
    void List() const;
    /// Write all DataFiles in list that have not yet been written.
    void WriteAllDF();
    void ResetWriteStatus();
    int ProcessDataFileArgs(ArgList&);
    int Debug() const { return debug_; }
  private:
    int GetCpptrajFileIdx(std::string const&) const;

    typedef std::vector<DataFile*> DFarray;
    DFarray fileList_;
    typedef std::vector<CpptrajFile*> CFarray;
    CFarray textList_;
    typedef std::vector<std::string> Sarray;
    Sarray textDescrip_; ///< Descriptions of each CpptrajFile
    typedef std::vector<CFtype> Tarray;
    Tarray textType_;
    int debug_;
#   ifdef MPI
    int ensembleMode_; ///< When parallel reading, append filenames with this
#   endif
};
#endif
