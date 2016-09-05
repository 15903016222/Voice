#ifndef PUSHBOTTONDELEGATE
#define PUSHBOTTONDELEGATE

#include <QItemDelegate>
#include <QPushButton>

class PushButtonDelegate : public QItemDelegate
{
	Q_OBJECT

public:
	explicit PushButtonDelegate(QObject *parent = 0);
	~PushButtonDelegate();
	void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
	bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index);
	QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;
	void drawDisplay(QPainter *painter, const QStyleOptionViewItem &option, const QRect &rect, const QString &text) const;
	bool switchFlag;
	void setSwitchFlag(QModelIndex index);
	QMap<QModelIndex, QStyleOptionButton*> buttonMap;

	//    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
	//    void setEditorData(QWidget *editor, const QModelIndex &index) const;
	//    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
	//    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;


	QPushButton *pushButton;
	QList<QModelIndex> modelIndex;
	//    QMap<QModelIndex, QPushButton*> buttonMap;

	//    void change_editor_text(QModelIndex index);
	//    bool eventFilter(QObject *object, QEvent *event);


};

#endif // PUSHBOTTONDELEGATE
