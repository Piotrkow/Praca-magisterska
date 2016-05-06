
(function(compId){var _=null,y=true,n=false,zy='scaleY',x3='6.0.0.400',x2='5.0.0',x5='rgba(0,0,0,0)',lf='left',e8='${youtube}',x9='632px',zx='scaleX',x4='both',x12='750px',x7='rgba(255,255,255,1)',tp='top',m='rect',x11='1200px',x10='352px',x1='6.0.0',g='image',i='none';var g6='1180x400_back.jpg';var im='images/',aud='media/',vid='media/',js='js/',fonts={},opts={'gAudioPreloadPreference':'auto','gVideoPreloadPreference':'auto'},resources=[],scripts=[],symbols={"stage":{v:x1,mv:x2,b:x3,stf:x4,cg:i,rI:n,cn:{dom:[{id:'_1180x400_back',t:g,r:['0','0','1180px','400px','auto','auto'],f:[x5,im+g6,'0px','0px']},{id:'youtube',symbolName:'youtube',t:m,r:['579px','-6px','632','352','auto','auto'],tf:[[],[],[],['0.84494','0.85227']]}],style:{'${Stage}':{isStage:true,r:['null','null','1180px','400px','auto','auto'],zr:['1180px','1180px','',''],overflow:'hidden',f:[x7]}}},tt:{d:0,a:y,data:[["eid21",zx,0,0,"linear",e8,'0.84494','0.84494'],["eid22",lf,0,0,"linear",e8,'579px','579px'],["eid3",zy,0,0,"linear",e8,'0.85227','0.85227'],["eid19",tp,0,0,"linear",e8,'-6px','-6px']]}},"youtube":{v:x1,mv:x2,b:x3,stf:i,cg:i,rI:n,cn:{dom:[],style:{'${symbolSelector}':{r:[_,_,x9,x10]}}},tt:{d:0,a:y,data:[]}},"ClickTag1":{v:x1,mv:x2,b:x3,stf:i,cg:i,rI:n,cn:{dom:[],style:{'${symbolSelector}':{r:[_,_,x11,x12]}}},tt:{d:0,a:y,data:[]}}};AdobeEdge.registerCompositionDefn(compId,symbols,fonts,scripts,resources,opts);})("EDGE-88560702");
(function($,Edge,compId){var Composition=Edge.Composition,Symbol=Edge.Symbol;Edge.registerEventBinding(compId,function($){
//Edge symbol: 'stage'
(function(symbolName){Symbol.bindElementAction(compId,symbolName,"document","compositionReady",function(sym,e){sym.$("youtube").attr('id','player');window.onYouTubeIframeAPIReady=function(){window.player=new YT.Player('player',{height:'300',width:'534',videoId:'lWbCAoa0tss',events:{'onReady':onPlayerReady}});};window.onPlayerReady=function(event){event.target.playVideo();window.player.mute();};(function(){var s=document.createElement('script');s.type='text/javascript';s.async=true;s.src='http://www.youtube.com/iframe_api';var x=document.getElementsByTagName('script')[0];x.parentNode.insertBefore(s,x);})();});
//Edge binding end
})("stage");
//Edge symbol end:'stage'

//=========================================================

//Edge symbol: 'youtube'
(function(symbolName){})("youtube");
//Edge symbol end:'youtube'

//=========================================================

//Edge symbol: 'ClickTag1'
(function(symbolName){})("ClickTag1");
//Edge symbol end:'ClickTag1'
})})(AdobeEdge.$,AdobeEdge,"EDGE-88560702");