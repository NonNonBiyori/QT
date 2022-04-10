/*
* ÖÐÎÄÂÒÂë×ª»»
*    
    const QString inputPath;
#if HR_WIN
    setConfig("file_input","file_path",utf82gbk(inputPath));
#else
setConfig("file_input","file_path",gbk2utf8(inputPath));
#endif

    std::string config;
#if HR_WIN
    ui->setText(utf82gbk(config));
#else
    ui->setText(gbk2utf8(config));
#endif
*/
#ifndef UITLS_UI_H
#define UITLS_UI_H
#include <QString>
#include <QTextCodec>

static QString gbk2utf8(const std::string& cstr)
{
    QTextCodec* pCodec = QTextCodec::codecForName("utf-8");
    if(!pCodec) return "";

    QString qstr = pCodec->toUnicode(cstr.c_str(), (int)cstr.length());
    return qstr;
}

static std::string gbk2utf8(const QString& cstr)
{
    QTextCodec* pCodec = QTextCodec::codecForName("utf-8");
    if(!pCodec) return "";

    QByteArray utf_bytes = pCodec->fromUnicode(cstr);
    std::string utfStr(utf_bytes.data());
    return utfStr;
}

static QString utf82gbk(const std::string& cstr)
{
        QTextCodec* pCodec = QTextCodec::codecForName("gb2312");
        if (!pCodec) return "";

        QString qstr = pCodec->toUnicode(cstr.c_str(), (int)cstr.length());
        return qstr;
}

static std::string utf82gbk(const QString& cstr)
{
        QTextCodec* pCodec = QTextCodec::codecForName("gb2312");
        if (!pCodec) return "";

        QByteArray gb_bytes = pCodec->fromUnicode(cstr);
        std::string gbkStr(gb_bytes.data());
        return gbkStr;
}
#endif // UITLS_UI_H
