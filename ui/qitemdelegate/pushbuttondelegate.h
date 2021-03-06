#ifndef PUSHBUTTONDELEGATE
#define PUSHBUTTONDELEGATE

#include <QStyledItemDelegate>

class PushButtonDelegate : public QStyledItemDelegate
{
	Q_OBJECT

public:
	explicit PushButtonDelegate(QObject *parent = 0);
	~PushButtonDelegate();

	void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
	bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index);
	QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;
	void drawDisplay(QPainter *painter, const QStyleOptionViewItem &option, const QRect &rect, const QString &text) const;	
    void set_switch_flag(QModelIndex index);
    void change_button_text(QModelIndex &index);

	QMap<QModelIndex, QStyleOptionButton*> buttonMap;

private:
    bool m_switchFlag;

signals:
    void switchPress(bool flag);

};

#endif // PUSHBUTTONDELEGATE
