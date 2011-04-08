
$(document).ready(function() {
  
  // Bind focus to fields
  // Show/hide original content
  $('textarea, input[id^=edit-field-data-translated]').bind('focus', function() {
    var hide = $(this).parents('fieldset').find('.original_data');
    if (hide.is(':hidden')) {
      $('.original_data:visible').slideUp();
      hide.slideDown();
    }
  });
  
  // Check if all translated
  // Focus to first untranslated field
  iclTranslateEditorCheckFinished();
  
  // Sets autosave interval
  if (Drupal.settings.icl_translate_editor_disable_autosave === undefined) {
    iclAjaxAutoSave('#icl-translate-editor', 60000); // 60 sec.
  }

  // Binds click to 'finished'
  // Submits AJAX autosave
  // Focuses and scrolls to next/first untranslated field
  $('#icl-translate-editor .finished').click(function() {
    iclAjaxSubmit('#icl-translate-editor');
    
    // If unchecked focus to it's field
    if ($(this).is(':checked') == false) {
       $(this).parents('fieldset').find('[id^=edit-field-data-translated]').focus();
       $('#icl-translate-editor-finished').attr('disabled', 1);
       $('#icl-translate-editor-finished').attr('checked', 0);
    // Else find next field
    } else {
      var fieldset = $(this).parents('fieldset').next('fieldset');
      var finished = fieldset.find('.finished');
      
      // If next fieldset not found check all/find first untranslated field
      if (finished.length == 0) {
        iclTranslateEditorCheckFinished();
      }
      // If next not marked as translated focus
      else if (finished.is(':checked') == false) {
        iclTranslateFocus(fieldset.find('[id^=edit-field-data-translated]'));
        $('#icl-translate-editor-finished').attr('disabled', 1);
        $('#icl-translate-editor-finished').attr('checked', 0);
      // Check other fields
      } else {
        iclTranslateEditorCheckFinished();
      }
    }
  });
  
  
  
  // Replaces translated conent with autosaved content
  $('.icl_translate_editor_load_autosave').click(function() {
    var toLoad = $(this).children('div');
    var toLoadData = toLoad.html();
    var toReplace = $(this).parent().children().find('[id^=edit-field-data-translated]');
    var toReplaceData = toReplace.val();
    toReplace.val('...');
    var timerCallback = function() {
      toReplace.val(toLoadData);
      toLoad.html(toReplaceData);
    };
    setTimeout(timerCallback, 200);
  });
  
  // Disable format change
  $('[id^=edit-body-field-data-translated-format]').find('input').each(function() {
      $(this).attr('disabled', 'disabled');
      $(this).unbind('click');
      if ($(this).is(':checked') == false) {
        $(this).parent().parent().css('display','none');
      }
    }
  );
  
  // Keyboard
  $('textarea, input[id^=edit-field-data-translated]').bind('keydown', 'ctrl+space', iclTranslateEditorKeyFinish);

  // Prevent unload if form is submitted
  $('#icl-translate-editor').submit(function() {
    window.onbeforeunload = '';
  });

  // Download XLIFF page reload
  $('#edit-download-xliff').click(function() {
    $(document).focus(function() {
      location.reload(true);
    });
  });
});

 /**
 * Checks if all translations are finished
 * Enables submit button
 * Focuses/scrolls to first untranslated field
 */
function iclTranslateEditorCheckFinished() {
  $('#icl-translate-editor .finished').each(function(e) {
    if ($(this).is(':checked') == false) {
      $('#icl-translate-editor-finished').attr('disabled', 1);
      $('#icl-translate-editor-finished').attr('checked', 0);
      iclTranslateFocus($(this).parents('fieldset').find('[id^=edit-field-data-translated]'));
      return false;
    } else {
      $('#icl-translate-editor-finished').attr('disabled', 0);
      //$('#icl-translate-editor-finished').attr('checked', 1);
    }
  });
}

/**
 * Focuses and scrolls to field
 */
function iclTranslateFocus(focusTo) {
  var x = focusTo.offset().top - 100; // 100 provides buffer in viewport
  $('html,body').animate({scrollTop: x}, 500);
  focusTo.focus();
}

/**
 * Handle if leaving page
 */
function iclTranslateEditorLeavePage() {
  if (Drupal.settings.icl_translate_editor_disable_leave !== undefined) {
    return false;
  }
  window.onbeforeunload = function (evt) {
    //var data = ;
    
    var form_id = 'icl_translate_editor';
    var form_token = $('#edit-icl-translate-editor-form-token').val();
    
    jQuery.ajax({
        type:   "POST",
        url: Drupal.settings.icl_editor_unload.ajax_url,
        data: {icl_translator_ajx_action:'translator_remove',
                uid:Drupal.settings.icl_editor_unload.uid,
                rid:Drupal.settings.icl_editor_unload.rid,
                form_id:form_id,
                form_token:form_token},
        cache: false,
        dataType: 'json',
        success: function(msg){
            if(!msg.error){
            }            
        }
    });
    return alert(Drupal.settings.icl_editor_unload.message);
  }
}

/**
 * Keyboard
 */

function iclTranslateEditorKeyFinish() {
  $(this).parents('fieldset').find('.finished').attr('checked', 1);
  iclTranslateEditorCheckFinished();
}

/*
(c) Copyrights 2007 - 2008

Original idea by by Binny V A, http://www.openjs.com/scripts/events/keyboard_shortcuts/
 
jQuery Plugin by Tzury Bar Yochay 
tzury.by@gmail.com
http://evalinux.wordpress.com
http://facebook.com/profile.php?id=513676303

Project's sites: 
http://code.google.com/p/js-hotkeys/
http://github.com/tzuryby/hotkeys/tree/master

License: same as jQuery license. 

USAGE:
    // simple usage
    $(document).bind('keydown', 'Ctrl+c', function(){ alert('copy anyone?');});
    
    // special options such as disableInIput
    $(document).bind('keydown', {combi:'Ctrl+x', disableInInput: true} , function() {});
    
Note:
    This plugin wraps the following jQuery methods: $.fn.find, $.fn.bind and $.fn.unbind
*/

(function (jQuery){
    // keep reference to the original $.fn.bind, $.fn.unbind and $.fn.find
    jQuery.fn.__bind__ = jQuery.fn.bind;
    jQuery.fn.__unbind__ = jQuery.fn.unbind;
    jQuery.fn.__find__ = jQuery.fn.find;
    
    var hotkeys = {
        version: '0.7.9',
        override: /keypress|keydown|keyup/g,
        triggersMap: {},
        
        specialKeys: { 27: 'esc', 9: 'tab', 32:'space', 13: 'return', 8:'backspace', 145: 'scroll', 
            20: 'capslock', 144: 'numlock', 19:'pause', 45:'insert', 36:'home', 46:'del',
            35:'end', 33: 'pageup', 34:'pagedown', 37:'left', 38:'up', 39:'right',40:'down', 
            109: '-', 
            112:'f1',113:'f2', 114:'f3', 115:'f4', 116:'f5', 117:'f6', 118:'f7', 119:'f8', 
            120:'f9', 121:'f10', 122:'f11', 123:'f12', 191: '/'},
        
        shiftNums: { "`":"~", "1":"!", "2":"@", "3":"#", "4":"$", "5":"%", "6":"^", "7":"&", 
            "8":"*", "9":"(", "0":")", "-":"_", "=":"+", ";":":", "'":"\"", ",":"<", 
            ".":">",  "/":"?",  "\\":"|" },
        
        newTrigger: function (type, combi, callback) { 
            // i.e. {'keyup': {'ctrl': {cb: callback, disableInInput: false}}}
            var result = {};
            result[type] = {};
            result[type][combi] = {cb: callback, disableInInput: false};
            return result;
        }
    };
    // add firefox num pad char codes
    //if (jQuery.browser.mozilla){
    // add num pad char codes
    hotkeys.specialKeys = jQuery.extend(hotkeys.specialKeys, { 96: '0', 97:'1', 98: '2', 99: 
        '3', 100: '4', 101: '5', 102: '6', 103: '7', 104: '8', 105: '9', 106: '*', 
        107: '+', 109: '-', 110: '.', 111 : '/'
        });
    //}
    
    // a wrapper around of $.fn.find 
    // see more at: http://groups.google.com/group/jquery-en/browse_thread/thread/18f9825e8d22f18d
    jQuery.fn.find = function( selector ) {
        this.query = selector;
        return jQuery.fn.__find__.apply(this, arguments);
  };
    
    jQuery.fn.unbind = function (type, combi, fn){
        if (jQuery.isFunction(combi)){
            fn = combi;
            combi = null;
        }
        if (combi && typeof combi === 'string'){
            var selectorId = ((this.prevObject && this.prevObject.query) || (this[0].id && this[0].id) || this[0]).toString();
            var hkTypes = type.split(' ');
            for (var x=0; x<hkTypes.length; x++){
                delete hotkeys.triggersMap[selectorId][hkTypes[x]][combi];
            }
        }
        // call jQuery original unbind
        return  this.__unbind__(type, fn);
    };
    
    jQuery.fn.bind = function(type, data, fn){
        // grab keyup,keydown,keypress
        var handle = type.match(hotkeys.override);
        
        if (jQuery.isFunction(data) || !handle){
            // call jQuery.bind only
            return this.__bind__(type, data, fn);
        }
        else{
            // split the job
            var result = null,            
            // pass the rest to the original $.fn.bind
            pass2jq = jQuery.trim(type.replace(hotkeys.override, ''));
            
            // see if there are other types, pass them to the original $.fn.bind
            if (pass2jq){
                result = this.__bind__(pass2jq, data, fn);
            }            
            
            if (typeof data === "string"){
                data = {'combi': data};
            }
            if(data.combi){
                for (var x=0; x < handle.length; x++){
                    var eventType = handle[x];
                    var combi = data.combi.toLowerCase(),
                        trigger = hotkeys.newTrigger(eventType, combi, fn),
                        selectorId = ((this.prevObject && this.prevObject.query) || (this[0].id && this[0].id) || this[0]).toString();
                        
                    //trigger[eventType][combi].propagate = data.propagate;
                    trigger[eventType][combi].disableInInput = data.disableInInput;
                    
                    // first time selector is bounded
                    if (!hotkeys.triggersMap[selectorId]) {
                        hotkeys.triggersMap[selectorId] = trigger;
                    }
                    // first time selector is bounded with this type
                    else if (!hotkeys.triggersMap[selectorId][eventType]) {
                        hotkeys.triggersMap[selectorId][eventType] = trigger[eventType];
                    }
                    // make trigger point as array so more than one handler can be bound
                    var mapPoint = hotkeys.triggersMap[selectorId][eventType][combi];
                    if (!mapPoint){
                        hotkeys.triggersMap[selectorId][eventType][combi] = [trigger[eventType][combi]];
                    }
                    else if (mapPoint.constructor !== Array){
                        hotkeys.triggersMap[selectorId][eventType][combi] = [mapPoint];
                    }
                    else {
                        hotkeys.triggersMap[selectorId][eventType][combi][mapPoint.length] = trigger[eventType][combi];
                    }
                    
                    // add attribute and call $.event.add per matched element
                    this.each(function(){
                        // jQuery wrapper for the current element
                        var jqElem = jQuery(this);
                        
                        // element already associated with another collection
                        if (jqElem.attr('hkId') && jqElem.attr('hkId') !== selectorId){
                            selectorId = jqElem.attr('hkId') + ";" + selectorId;
                        }
                        jqElem.attr('hkId', selectorId);
                    });
                    result = this.__bind__(handle.join(' '), data, hotkeys.handler)
                }
            }
            return result;
        }
    };
    // work-around for opera and safari where (sometimes) the target is the element which was last 
    // clicked with the mouse and not the document event it would make sense to get the document
    hotkeys.findElement = function (elem){
        if (!jQuery(elem).attr('hkId')){
            if (jQuery.browser.opera || jQuery.browser.safari){
                while (!jQuery(elem).attr('hkId') && elem.parentNode){
                    elem = elem.parentNode;
                }
            }
        }
        return elem;
    };
    // the event handler
    hotkeys.handler = function(event) {
        var target = hotkeys.findElement(event.currentTarget), 
            jTarget = jQuery(target),
            ids = jTarget.attr('hkId');
        
        if(ids){
            ids = ids.split(';');
            var code = event.which,
                type = event.type,
                special = hotkeys.specialKeys[code],
                // prevent f5 overlapping with 't' (or f4 with 's', etc.)
                character = !special && String.fromCharCode(code).toLowerCase(),
                shift = event.shiftKey,
                ctrl = event.ctrlKey,            
                // patch for jquery 1.2.5 && 1.2.6 see more at:  
                // http://groups.google.com/group/jquery-en/browse_thread/thread/83e10b3bb1f1c32b
                alt = event.altKey || event.originalEvent.altKey,
                mapPoint = null;

            for (var x=0; x < ids.length; x++){
                if (hotkeys.triggersMap[ids[x]][type]){
                    mapPoint = hotkeys.triggersMap[ids[x]][type];
                    break;
                }
            }
            
            //find by: id.type.combi.options            
            if (mapPoint){ 
                var trigger;
                // event type is associated with the hkId
                if(!shift && !ctrl && !alt) { // No Modifiers
                    trigger = mapPoint[special] ||  (character && mapPoint[character]);
                }
                else{
                    // check combinations (alt|ctrl|shift+anything)
                    var modif = '';
                    if(alt) modif +='alt+';
                    if(ctrl) modif+= 'ctrl+';
                    if(shift) modif += 'shift+';
                    // modifiers + special keys or modifiers + character or modifiers + shift character or just shift character
                    trigger = mapPoint[modif+special];
                    if (!trigger){
                        if (character){
                            trigger = mapPoint[modif+character] 
                                || mapPoint[modif+hotkeys.shiftNums[character]]
                                // '$' can be triggered as 'Shift+4' or 'Shift+$' or just '$'
                                || (modif === 'shift+' && mapPoint[hotkeys.shiftNums[character]]);
                        }
                    }
                }
                if (trigger){
                    var result = false;
                    for (var x=0; x < trigger.length; x++){
                        if(trigger[x].disableInInput){
                            // double check event.currentTarget and event.target
                            var elem = jQuery(event.target);
                            if (jTarget.is("input") || jTarget.is("textarea") || jTarget.is("select") 
                                || elem.is("input") || elem.is("textarea") || elem.is("select")) {
                                return true;
                            }
                        }                       
                        // call the registered callback function
                        result = result || trigger[x].cb.apply(this, [event]);
                    }
                    return result;
                }
            }
        }
    };
    // place it under window so it can be extended and overridden by others
    window.hotkeys = hotkeys;
    return jQuery;
})(jQuery);