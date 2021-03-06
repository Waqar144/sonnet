/*
 * kspell_hunspellclient.cpp
 *
 * SPDX-FileCopyrightText: 2009 Montel Laurent <montel@kde.org>
 *
 * SPDX-License-Identifier: LGPL-2.1-or-later
 */
#include "hunspellclient.h"
#include "hunspelldict.h"
#include "hunspelldebug.h"

#include <QDir>
#include <QString>
#include <QStandardPaths>

using namespace Sonnet;

HunspellClient::HunspellClient(QObject *parent)
    : Client(parent)
{
    qCDebug(SONNET_HUNSPELL) << " HunspellClient::HunspellClient";

    QStringList dirList;
    // search QStandardPaths
    dirList.append(QStandardPaths::locateAll(
                       QStandardPaths::GenericDataLocation,
                       QStringLiteral("hunspell"),
                       QStandardPaths::LocateDirectory));

    auto maybeAddPath = [&dirList](const QString &path)
    {
        if (QFileInfo::exists(path)) {
            dirList.append(path);

            QDir dir(path);
            for (const QString &subDir : dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot)) {
                dirList.append(dir.absoluteFilePath(subDir));
            }

        }
    };
#ifdef Q_OS_WIN
    maybeAddPath(QStringLiteral(SONNET_INSTALL_PREFIX "/bin/data/hunspell/"));
#else
    maybeAddPath(QStringLiteral("/System/Library/Spelling"));
    maybeAddPath(QStringLiteral("/usr/share/hunspell/"));
    maybeAddPath(QStringLiteral("/usr/share/myspell/"));
#endif

    for (const QString &dirString : dirList) {
        QDir dir(dirString);
        const auto dicts = dir.entryInfoList({QStringLiteral("*.aff")}, QDir::Files);
        for (const QFileInfo &dict : dicts) {
            m_languagePaths.insert(dict.baseName(), dict.canonicalPath());
        }
    }
}

HunspellClient::~HunspellClient()
{
}

SpellerPlugin *HunspellClient::createSpeller(const QString &language)
{
    qCDebug(SONNET_HUNSPELL)
    << " SpellerPlugin *HunspellClient::createSpeller(const QString &language) ;" << language;
    HunspellDict *ad = new HunspellDict(language, m_languagePaths.value(language));
    return ad;
}

QStringList HunspellClient::languages() const
{
    return m_languagePaths.keys();
}
