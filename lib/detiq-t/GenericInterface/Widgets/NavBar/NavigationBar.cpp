/*
 * Copyright 2011-2012 Benoit Averty, Samuel Babin, Matthieu Bergere, Thomas Letan, Sacha Percot-Tétu, Florian Teyssier
 * 
 * This file is part of DETIQ-T.
 * 
 * DETIQ-T is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * DETIQ-T is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with DETIQ-T.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "NavigationBar.h"
#include <iostream>
#include <QMouseEvent>

using namespace genericinterface;
using namespace imagein;

NavigationBar::NavigationBar(QSize itemSize, Qt::Orientation orientation) : QListView(), _itemSize(itemSize), _mouseDown(false)
{
    setEditTriggers(QAbstractItemView::NoEditTriggers);
    
    setSelectionMode(QAbstractItemView::ExtendedSelection);
    setDragEnabled(true);
    viewport()->setAcceptDrops(true);
    setDropIndicatorShown(true);
    setDragDropMode(DragDrop);
    setAcceptDrops(true);
    
    if(orientation == Qt::Horizontal) {
        this->setFlow(LeftToRight);
        this->setSizePolicy(QSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed));
    }
    else {
        this->setFlow(TopToBottom);
        this->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::MinimumExpanding));
    }
}

void NavigationBar::mousePressEvent(QMouseEvent* event) {
    //std::cout << "NavigationBar::mousePressEvent : " << event->x() << ':' << event->y() << std::endl;
    _mouseDown = true;
    _downPos = event->pos();
    QListView::mousePressEvent(event);
}

void NavigationBar::mouseReleaseEvent(QMouseEvent* event) {
    //std::cout << "NavigationBar::mouseReleaseEvent : " << event->x() << ':' << event->y() << std::endl;
    
    QListView::mouseReleaseEvent(event);
    if(_mouseDown) {
        QPoint upPos = event->pos();
        QModelIndex downIndex = this->indexAt(_downPos);
        QModelIndex upIndex = this->indexAt(upPos);
        
        if(downIndex.isValid() && upIndex.isValid() && downIndex==upIndex) {
            emit itemClicked(upIndex, _downPos, upPos);
        }
    }
    
}

QSize NavigationBar::sizeHintForIndex(const QModelIndex& index) const {
    QVariant data = index.data();
    if(data.canConvert<const Node*>()) {
        const Node* node = data.value<const Node*>();
        if(node != NULL) {
            const Image* img = node->image;
            if(img != NULL) {
                if(img->getWidth() > img->getHeight()) {
                    double ratio = (double)img->getHeight() / (double)img->getWidth();
                    return QSize(_itemSize.width(), _itemSize.height()*ratio);
                }
                else if(img->getWidth() < img->getHeight()){
                    double ratio = (double)img->getWidth() / (double)img->getHeight();
                    return QSize(_itemSize.width()*ratio, _itemSize.height());
                }
                else {
                    return _itemSize;
                }
                
            }
        }
    }
    return QSize();
}

QSize NavigationBar::sizeHint() const {
    return _itemSize+QSize(24,24);
    return QListView::sizeHint();
}

void NavigationBar::setOrientation(Qt::Orientation orientation) {
    //std::cout << "NavigationBar::setOrientation" << (orientation == Qt::Horizontal ? "Horizontal" : "Vertical") << std::endl;
    if(orientation == Qt::Horizontal) {
        //std::cout << "NavigationBar::setOrientation" << "Horizontal" << std::endl;
        this->setFlow(LeftToRight);
        this->setSizePolicy(QSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred));
    }
    else {
        //std::cout << "NavigationBar::setOrientation" << "Vertical" << std::endl;
        this->setFlow(TopToBottom);
        this->setSizePolicy(QSizePolicy(QSizePolicy::Preferred, QSizePolicy::MinimumExpanding));
    }
    emit resized();
}

void NavigationBar::resizeEvent(QResizeEvent* e) {
    /*if(this->width() > this->height()) {
        this->setFlow(LeftToRight);
        //this->resize(this->width(), _itemSize.height()+24);
        this->setSizePolicy(QSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed));
        
    }
    else {
        this->setFlow(TopToBottom);
        //this->resize(_itemSize.width()+24, this->height());
        this->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::MinimumExpanding));
    }
    emit resized();*/
    
    QListView::resizeEvent(e);
}
