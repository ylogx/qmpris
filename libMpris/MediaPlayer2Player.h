#ifndef MEDIAPLAYER2_PLAYER_HEADER
#define MEDIAPLAYER2_PLAYER_HEADER

#include <QtGui>
#include <QtDBus/QtDBus>
#include <QtDBus/QDBusMessage>
#include <QtDBus/QDBusConnection>

namespace QMpris{
    class MediaPlayer2Player : public QObject {
        Q_OBJECT
    private:
        //
    public:
        explicit MediaPlayer2Player( QObject* parent = 0);
        ~MediaPlayer2Player();
    public:
        bool CanGoNext() const;
/*
        QString PlaybackStatus() const;
        QString LoopStatus() const;
        void setLoopStatus( const QString& loopStatus ) const;
        double Rate() const;
        void setRate( double rate ) const;
        bool Shuffle() const;
        void setShuffle( bool shuffle ) const;
        QVariantMap Metadata() const;
        double Volume() const;
        void setVolume( double volume ) const;
        qlonglong Position() const;
        double MinimumRate() const;
        double MaximumRate() const;
        bool CanGoNext() const;
        bool CanGoPrevious() const;
        bool CanPlay() const;
        bool CanPause() const;
        bool CanSeek() const;
        bool CanControl() const;
    
    Q_SIGNALS:
        void Seeked( qlonglong Position ) const;
    
    public slots:
        void Next() const;
        void Previous() const;
        void Pause() const;
        void PlayPause() const;
        void Stop() const;
        void Play() const;
        void Seek( qlonglong Offset ) const;
        void SetPosition( const QDBusObjectPath& TrackId, qlonglong Position ) const;
        void OpenUri( QString Uri ) const;
    
    private slots:
        void trackPositionChanged( qint64 position, bool userSeek );
        void trackChanged();    // Meta::AlbumPtr album );
        void trackMetadataChanged();
        void albumMetadataChanged();
        void seekableChanged( bool seekable );
        void volumeChanged( int newVolPercent );
        void trackLengthChanged( qint64 milliseconds );
        void playbackStateChanged();
        void playlistNavigatorChanged();
        void playlistRowsInserted( QModelIndex, int, int );
        void playlistRowsMoved( QModelIndex, int, int, QModelIndex, int );
        void playlistRowsRemoved( QModelIndex, int, int );
        void playlistReplaced();
        void playlistActiveTrackChanged( quint64 );

    private:
        QVariantMap metadataForTrack( );    //Meta::TrackPtr track ) const;
        qint64 m_lastPosition;
*/
    };
}

#endif //MEDIAPLAYER2_PLAYER_HEADER

