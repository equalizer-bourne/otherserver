// **********************************************************************
// This file was generated by a TAF parser!
// TAF version 1.3.1 by WSRD Tencent.
// Generated from `Hello.jce'
// **********************************************************************

#include "Hello.h"
#include "jce/wup.h"
#include "servant/BaseF.h"

using namespace wup;

namespace Test
{

    taf::Int32 HelloProxy::testHello(const std::string &s, std::string &r, const map<string, string> &context)
    {
        taf::JceOutputStream<taf::BufferWriter> _os;
        _os.write(s, 1);
        _os.write(r, 2);
        taf::ResponsePacket rep;
        std::map<string, string> status;
        taf_invoke(taf::JCENORMAL,"testHello", _os.getByteBuffer(), context, status, rep);
        taf::JceInputStream<taf::BufferReader> _is;
        _is.setBuffer(rep.sBuffer);
        taf::Int32 _ret;
        _is.read(_ret, 0, true);
        _is.read(r, 2, true);
        return _ret;
    }

    void Hello::async_response_testHello(taf::JceCurrentPtr current, taf::Int32 _ret, const std::string &r)
    {
        taf::JceOutputStream<taf::BufferWriter> _os;
        _os.write(_ret, 0);

        _os.write(r, 2);

        current->sendResponse(taf::JCESERVERSUCCESS, _os.getByteBuffer());
    }

    void HelloProxy::async_testHello(HelloPrxCallbackPtr callback,const std::string &s,const map<string, string>& context)
    {
        taf::JceOutputStream<taf::BufferWriter> _os;
        _os.write(s, 1);
        std::map<string, string> status;
        taf_invoke_async(taf::JCENORMAL,"testHello", _os.getByteBuffer(), context, status, callback);
    }

    HelloProxy* HelloProxy::taf_hash(int64_t key)
    {
        return (HelloProxy*)ServantProxy::taf_hash(key);
    }

    static ::std::string __Test__Hello_all[]=
    {
        "testHello"
    };

    int HelloPrxCallback::onDispatch(taf::ReqMessagePtr msg)
    {
        pair<string*, string*> r = equal_range(__Test__Hello_all, __Test__Hello_all+1, msg->request.sFuncName);
        if(r.first == r.second) return taf::JCESERVERNOFUNCERR;
        switch(r.first - __Test__Hello_all)
        {
            case 0:
            {
                if (msg->response.iRet != taf::JCESERVERSUCCESS)
                {
                    callback_testHello_exception(msg->response.iRet);

                    return msg->response.iRet;
                }
                taf::JceInputStream<taf::BufferReader> _is;

                _is.setBuffer(msg->response.sBuffer);
                taf::Int32 _ret;
                _is.read(_ret, 0, true);

                std::string r;
                _is.read(r, 2, true);
                callback_testHello(_ret, r);
                return taf::JCESERVERSUCCESS;

            }
        }
        return taf::JCESERVERNOFUNCERR;
    }

    int Hello::onDispatch(taf::JceCurrentPtr _current, vector<char> &_sResponseBuffer)
    {
        pair<string*, string*> r = equal_range(__Test__Hello_all, __Test__Hello_all+1, _current->getFuncName());
        if(r.first == r.second) return taf::JCESERVERNOFUNCERR;
        switch(r.first - __Test__Hello_all)
        {
            case 0:
            {
                taf::JceInputStream<taf::BufferReader> _is;
                _is.setBuffer(_current->getRequestBuffer());
                std::string s;
                std::string r;
                if (_current->getRequestVersion() == WUPVERSION)
                {
                    UniAttribute<taf::BufferWriter, taf::BufferReader>  tafAttr;
                    tafAttr.decode(_current->getRequestBuffer());
                    tafAttr.get("s", s);
                    tafAttr.getByDefault("r", r, r);
                }
                else
                {
                    _is.read(s, 1, true);
                    _is.read(r, 2, false);
                }
                taf::Int32 _ret = testHello(s,r, _current);
                if(_current->isResponse())
                {
                    if (_current->getRequestVersion() == WUPVERSION)
                    {
                        UniAttribute<taf::BufferWriter, taf::BufferReader>  tafAttr;
                        tafAttr.put("", _ret);
                        tafAttr.put("r", r);
                        tafAttr.encode(_sResponseBuffer);
                    }
                    else
                    {
                        taf::JceOutputStream<taf::BufferWriter> _os;
                        _os.write(_ret, 0);
                        _os.write(r, 2);
                        _os.swap(_sResponseBuffer);
                    }
                }
                return taf::JCESERVERSUCCESS;

            }
        }
        return taf::JCESERVERNOFUNCERR;
    }


}

