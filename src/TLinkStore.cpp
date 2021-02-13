/***************************************************************************
 *   Copyright (C) 2020 by Gustavo Sousa - gustavocms@gmail.com            *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include "TLinkStore.h"
#include "Host.h"

int TLinkStore::addLinks(Host *pH, const QStringList& links, const QStringList& hints, const QVector<bool> isFunctionList)
{
    if (++mLinkID > maxLinks) {
        mLinkID = 1;
    }

    // Used to unref lua objects in the registry to avoid memory leaks
    if (mLinkStore.contains(mLinkID)){
        QStringList oldLinks = mLinkStore.value(mLinkID);
        QVector<bool> oldIsFunction = mIsFunction.value(mLinkID);
        for (int i = 0, total = oldLinks.size(); i < total; ++i) {
            if (oldIsFunction.value(i, false)){
                pH->mLuaInterpreter.freeLuaRegistryIndex(oldLinks.at(i).toInt());
            }
        }
    }

    mLinkStore[mLinkID] = links;
    mHintStore[mLinkID] = hints;
    mIsFunction[mLinkID] = isFunctionList;

    return mLinkID;
}

QStringList TLinkStore::getCurrentLinks() const
{
    return mLinkStore.value(mLinkID);
}

void TLinkStore::setCurrentLinks(const QStringList& links)
{
    mLinkStore[mLinkID] = links;
}

QStringList& TLinkStore::getLinks(int id)
{
    return mLinkStore[id];
}

QStringList& TLinkStore::getHints(int id)
{
    return mHintStore[id];
}

QVector<bool> TLinkStore::getIsLinkFunction(int id) const
{
    return mIsFunction.value(id);
}

QStringList TLinkStore::getLinksConst(int id) const
{
    return mLinkStore.value(id);
}

QStringList TLinkStore::getHintsConst(int id) const
{
    return mHintStore.value(id);
}

int TLinkStore::getCurrentLinkID() const
{
    return mLinkID;
}
