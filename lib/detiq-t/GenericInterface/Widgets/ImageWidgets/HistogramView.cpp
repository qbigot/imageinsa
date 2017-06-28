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

#include "HistogramView.h"
#include <qwt_plot.h>

using namespace genericinterface;
using namespace imagein;

HistogramView::HistogramView(const Image* image, imagein::Rectangle rect, bool cumul)
    : GenericHistogramView(image, rect, false, 0, false, cumul)
{
    if(!cumul) {
        _qwtPlot->setTitle(tr("Histogram"));
    }
    else {
        _qwtPlot->setTitle(tr("Cumulated histogram"));
    }
}

HistogramView::HistogramView(const ImageDouble *image, Rectangle rect, bool cumul)
    : GenericHistogramView(image, rect, false, 0, false, cumul)
{
    if(!cumul) {
        _qwtPlot->setTitle(tr("Histogram"));
    }
    else {
        _qwtPlot->setTitle(tr("Cumulated histogram"));
    }
}

    
