#include <unistd.h>
#include <fcntl.h>
#include "CiOSPathConv.h"
#include "CiOSTmpFile.h"
#include "CPFInterface.h"

CiOSTmpFile::CiOSTmpFile(const char *path) : m_fullpath(0) {
	m_fullpath = CiOSPathConv::getInstance().fullpath(path);
	// 平成24年11月27日(火)
	// ファイルが存在しない場合に該当ファイルが生成されない事への対応と
	// 権限の付与を行いました。
	m_fd = open(m_fullpath, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	CPFInterface::getInstance().platform().excludePathFromBackup(m_fullpath);
}

CiOSTmpFile::~CiOSTmpFile() {
	if (m_fd > 0) {
		close(m_fd);
	}
	delete[] m_fullpath;
}

size_t CiOSTmpFile::writeTmp(void *ptr, size_t size) {
	return write(m_fd, ptr, size);
}
