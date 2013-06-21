/* === This file is part of Tomahawk Player - <http://tomahawk-player.org> ===
 *
 *   Copyright 2013, Dominik Schmidt <domme@tomahawk-player.org>
 *
 *   Tomahawk is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   Tomahawk is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with Tomahawk. If not, see <http://www.gnu.org/licenses/>.
 */

#include "ResolverDialog.h"
#include <resolvers/JSResolver.h>

#include <QVBoxLayout>
#include <QLabel>
#include <QDialogButtonBox>
#include <QPushButton>

ResolverDialog::ResolverDialog( JSResolver* resolver, QWidget* parent, Qt::WindowFlags f )
    : QDialog( parent, f )
    , m_resolver( 0 )
{
    QLayout* layout = new QVBoxLayout;
    layout->addWidget( (QWidget*)( resolver->configUI() ) );

    QDialogButtonBox* buttonBox = new QDialogButtonBox( QDialogButtonBox::Ok | QDialogButtonBox::Cancel );
    layout->addWidget( buttonBox );

    setLayout(layout);

    setWindowTitle( QString("Grindstone: %1").arg( resolver->name() ) );
    setWindowFlags( windowFlags() | (Qt::WindowFlags) Qt::WA_DeleteOnClose );

    connect( buttonBox->button( QDialogButtonBox::Ok ), SIGNAL( clicked() ), this, SLOT( accept() ) );
    connect( buttonBox->button( QDialogButtonBox::Cancel ), SIGNAL( clicked() ), this, SLOT( reject() ) );
}


ResolverDialog::~ResolverDialog()
{

}
