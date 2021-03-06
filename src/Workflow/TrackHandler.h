/*****************************************************************************
 * TrackHandler.h : Handle multiple track of a kind (audio or video)
 *****************************************************************************
 * Copyright (C) 2008-2010 VideoLAN
 *
 * Authors: Hugo Beauzee-Luyssen <hugo@vlmc.org>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston MA 02110-1301, USA.
 *****************************************************************************/

#ifndef TRACKHANDLER_H
#define TRACKHANDLER_H

#include <QObject>
#include "Toggleable.hpp"
#include "MainWorkflow.h"

//TEMPORARY:
#include "AudioClipWorkflow.h"

class   EffectEngine;
class   TrackWorkflow;

class   TrackHandler : public QObject
{
    Q_OBJECT
    public:
        TrackHandler( unsigned int nbTracks, MainWorkflow::TrackType trackType, EffectsEngine* effectsEngine );
        ~TrackHandler();

        void                    addClip( Clip* clip, unsigned int trackId, qint64 start );
        /**
         *  Returns the number of tracks in this handler
         */
        unsigned int            getTrackCount() const;
        qint64                  getLength() const;
        void                    startRender();
        /**
         *  \param      currentFrame    The current rendering frame (ie the video frame, in all case)
         *  \param      subFrame        The type-dependent frame. IE, for a video track,
         *                              it's the same as currentFrame, but for an audio
         *                              track, it will be different.
         *  \param      paused          The renderer paused state
         *  \todo       This should probably be partialy handled by the trackHandler, as the work
         *              is exactly the same for both audio and video trackWorkflow in most of the case... or not.
         */
        void                    getOutput( qint64 currentFrame, qint64 subFrame,
                                           bool paused );
        void                    activateAll();
        qint64                  getClipPosition( const QUuid& uuid, unsigned int trackId ) const;
        void                    stop();
        void                    moveClip( const QUuid& clipUuid, unsigned int oldTrack,
                                          unsigned int newTrack, qint64 startingFrame );
        Clip*                   removeClip( const QUuid& uuid, unsigned int trackId );
        void                    muteTrack( unsigned int trackId );
        void                    unmuteTrack( unsigned int trackId );
        Clip*                   getClip( const QUuid& uuid, unsigned int trackId );
        void                    clear();

        //FIXME: remove this. This should go by the effect engine.
        AudioClipWorkflow::AudioSample* getTmpAudioBuffer() { return m_tmpAudioBuffer; }

        bool                    endIsReached() const;

        void                    save( QDomDocument& doc, QDomElement& timelineNode ) const;

        /**
         *  \brief      Will configure the track workflow so they render only one frame
         *
         *  \sa MainWorkflow::renderOneFrame()
         */
        void                    renderOneFrame();

        /**
         *  \sa     MainWorkflow::setFullSpeedRender();
         */
        void                    setFullSpeedRender( bool val );

        /**
         *  \brief  Will mute a clip in the given track.
         *
         *  \param  uuid    The uuid of the clip to mute.
         *  \param  trackId The id of the track holding the clip.
         */
        void                    muteClip( const QUuid& uuid, quint32 trackId );
        void                    unmuteClip( const QUuid& uuid, quint32 trackId );

    private:
        void                    computeLength();
        void                    activateTrack( unsigned int tracKId );

    private:
        static LightVideoFrame*         nullOutput;
        Toggleable<TrackWorkflow*>*     m_tracks;
        unsigned int                    m_trackCount;
        MainWorkflow::TrackType         m_trackType;
        qint64                          m_length;
        unsigned int                    m_highestTrackNumber;
        bool                            m_endReached;
        EffectsEngine*                  m_effectEngine;
        AudioClipWorkflow::AudioSample* m_tmpAudioBuffer;


    private slots:
        void                            trackEndReached( unsigned int trackId );

    signals:
        void                            tracksEndReached();
};

#endif // TRACKHANDLER_H
