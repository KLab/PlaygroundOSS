#include <iostream>
#include "CiOSWidget.h"
#include "CiOSPlatform.h"
#import "CiOSWebView.h"
#include "CiOSPathConv.h"
#import <CoreMedia/CoreMedia.h>

CiOSWidget::CiOSWidget(CiOSPlatform *pParent)
: m_x(0)
, m_y(0)
, m_width(0)
, m_height(0)
, m_pPlatform(pParent) {
	m_scale = m_pPlatform->getScale();
}

CiOSWidget::~CiOSWidget() {
}

void CiOSWidget::cmd(int cmd, ...) {
}

int CiOSWidget::status() {
	return 0;
}

bool CiOSWidget::init(int id, int x, int y, int width, int height) {
	m_id = id;
	m_x = x;
	m_y = y;
	m_width = width;
	m_height = height;
	set_move(m_x, m_y, m_width, m_height);
	return true;
}

void CiOSWidget::move(int x, int y) {
	m_x = x;
	m_y = y;
	set_move(m_x, m_y, m_width, m_height);
}

void CiOSWidget::resize(int width, int height) {
	m_width = width;
	m_height = height;
	set_move(m_x, m_y, m_width, m_height);
}
